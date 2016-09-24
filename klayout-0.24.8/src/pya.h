
/*

  KLayout Layout Viewer
  Copyright (C) 2006-2016 Matthias Koefferlein

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

*/


#ifndef _HDR_pya
#define _HDR_pya

#if defined(HAVE_PYTHON)

#include "pyaRefs.h"

#include "gsi.h"
#include "gsiRuntimeError.h"
#include "gsiInterpreter.h"

#include <list>
#include <string>

struct _typeobject;
typedef _typeobject PyTypeObject;

struct _frame;
typedef _frame PyFrameObject;

struct PyMethodDef;
struct PyGetSetDef;

namespace gsi
{
  class MethodBase;
}

namespace pya
{

/**
 *  @brief The client slot for GSI
 *  This number must be between 0 and gsi::num_clients and must be unique.
 */
const int client_index = 1;

/**
 *  Two helper macros that frame a piece of code which potentially executes Python code
 */

#define PYTHON_BEGIN_EXEC \
  try { \
    PythonInterpreter::instance ()->begin_execution ();

#define PYTHON_END_EXEC \
    PythonInterpreter::instance ()->end_execution (); \
  } catch (...) { \
    PythonInterpreter::instance ()->end_execution (); \
    throw; \
  } 

/**
 *  @brief A class encapsulating a python exception
 */
class KLAYOUT_DLL PythonError
  : public gsi::RuntimeError
{
public:
  PythonError (const char *msg, const char *cls, const std::vector <gsi::BacktraceElement> &backtrace)
    : gsi::RuntimeError (msg, cls, backtrace)
  { }

  PythonError (const char *msg, const char *sourcefile, int line, const char *cls, const std::vector <gsi::BacktraceElement> &backtrace)
    : gsi::RuntimeError (msg, sourcefile, line, cls, backtrace)
  { }

  PythonError (const PythonError &d)
    : gsi::RuntimeError (d)
  { }
};

class MethodTable;

/**
 *  @brief The python interpreter wrapper class
 */
class KLAYOUT_DLL PythonInterpreter
  : public gsi::Interpreter
{
public:
  /**
   *  @brief The constructor 
   */
  PythonInterpreter ();

  /**
   *  @brief The destructor 
   */
  ~PythonInterpreter ();

  /**
   *  @brief Add the given path to the search path
   */
  void add_path (const std::string &path);

  /**
   *  @brief Requires the given module
   */
  void require (const std::string &filename);

  /**
   *  @brief Set the given debugger scope
   *
   *  The debugger scope is the element to which the back trace will be reduced.
   *  Specifically this suppresses calls from inner functions called from that file.
   *  This is useful for DSL implementations.
   */
  void set_debugger_scope (const std::string &filename);

  /**
   *  @brief Removes the debugger scope
   */
  void remove_debugger_scope ();

  /**
   *  @brief Ignores the next exception
   *
   *  This is useful for suppressing reraised exceptions in the debugger.
   */
  void ignore_next_exception ();

  /**
   *  @brief Load the given file
   */
  void load_file (const std::string &filename);

  /**
   *  @brief Implementatiom of gsi::Interpreter::eval_string
   */
  void eval_string (const char *string, const char *filename = 0, int line = 1, int context = -1);

  /**
   *  @brief Implementatiom of gsi::Interpreter::eval_expr
   */
  tl::Variant eval_expr (const char *string, const char *filename = 0, int line = 1, int context = -1);
 
  /**
   *  @brief Implementatiom of gsi::Interpreter::eval_string_and_print
   */ 
  void eval_string_and_print (const char *string, const char *filename = 0, int line = 1, int context = -1);

  /**
   *  @brief Returns an inspector for the given context
   */
  virtual gsi::Inspector *inspector (int context = -1);

  /**
   *  @brief Defines a global variable with the given name and value 
   */
  void define_variable (const std::string &name, const std::string &value);

  /**
   *  @brief Gets a value indicating whether the interpreter is available
   */
  bool available () const;

  /**
   *  @brief Installs the given console for output
   */
  void push_console (gsi::Console *console);

  /**
   *  @brief Removes the given console
   */
  void remove_console (gsi::Console *console);

  /**
   *  @brief Installs the given execution handler
   *
   *  The execution handler is informed when the interpreter enters code execution (also
   *  from the outside, i.e. a method reimplementing a C++ method or a event handler).
   *  During execution, the handler receives trace events which allow him to intercept
   *  execution.
   */
  void push_exec_handler (gsi::ExecutionHandler *exec_handler);

  /**
   *  @brief Removes the given execution handler
   */
  void remove_exec_handler (gsi::ExecutionHandler *exec_handler);

  /**
   *  @brief Fetch the version string
   *
   *  Returns an empty string when no Python interpreter is installed.
   */
  std::string version () const;

  /**
   *  @brief Gets the GSI class for a Python class
   */
  const gsi::ClassBase *cls_for_type (PyTypeObject *type) const;

  /**
   *  @brief The reverse: gets a Python class for a GSI class or NULL if there is no binding
   */
  PyTypeObject *type_for_cls (const gsi::ClassBase *cls) const;

  /**
   *  @brief Returns the current console
   */
  gsi::Console *current_console () const;

  /**
   *  @brief Indicates the start of execution of a Python script
   *  This method is intended for internal use.
   */
  void begin_execution ();

  /**
   *  @brief Indicates the end of execution of a Python script
   *  This method is intended for internal use.
   */
  void end_execution ();

  /**
   *  @brief Callback from the trace function
   */
  int trace_func (PyFrameObject *frame, int event, PyObject *arg);

  /**
   *  @brief Returns additional Python-specific documentation for the given method
   *  If no specific documentation exists, an empty string is returned.
   */
  std::string python_doc (const gsi::MethodBase *method) const;

  /**
   *  @brief Returns the singleton reference
   */
  static PythonInterpreter *instance ();

  /**
   *  @brief Provide a first (basic) initialization
   */
  static void initialize ();

private:
  size_t prepare_trace (PyObject *);
  tl::Variant eval_int (const char *string, const char *filename, int line, bool eval_expr, int context);
  void get_context (int context, PythonRef &globals, PythonRef &locals, const char *file);
  void add_python_doc (const gsi::ClassBase &cls, const MethodTable *mt, int mid, const std::string &doc);
  PyMethodDef *make_method_def ();
  PyGetSetDef *make_getset_def ();
  char *make_string (const std::string &s);

  std::list<PythonRef> m_object_heap;
  std::list<std::string> m_string_heap;
  std::map<const gsi::MethodBase *, std::string> m_python_doc;
  std::vector<PyMethodDef *> m_methods_heap;
  std::vector<PyGetSetDef *> m_getseters_heap;
  PythonRef m_stdout_channel, m_stderr_channel;
  PythonPtr m_stdout, m_stderr;

  std::map <PyTypeObject *, const gsi::ClassBase *> m_cls_map;
  std::map <const gsi::ClassBase *, PyTypeObject *> m_rev_cls_map;
  gsi::Console *mp_current_console;
  std::vector<gsi::Console *> m_consoles;
  gsi::ExecutionHandler *mp_current_exec_handler;
  std::vector<gsi::ExecutionHandler *> m_exec_handlers;

  //  trace function context
  int m_current_exec_level;
  bool m_in_trace;
  bool m_block_exceptions;
  bool m_ignore_next_exception;
  std::string m_debugger_scope;
  PyFrameObject *mp_current_frame;
  std::map<PyObject *, size_t> m_file_id_map;
  wchar_t *mp_py3_app_name;
};

}

#else

#include "gsiInterpreter.h"

namespace gsi
{
  class MethodBase;
}

namespace pya
{

/**
 *  @brief The dummy interpreter class if Python is not available
 */
class KLAYOUT_DLL PythonInterpreter
  : public gsi::Interpreter
{
public:
  PythonInterpreter ();
  ~PythonInterpreter ();

  /**
   *  @brief Add the given path to the search path
   */
  void add_path (const std::string &path);

  /**
   *  @brief Requires the given module
   */
  void require (const std::string &filename);

  /**
   *  @brief Set the given debugger scope
   *
   *  The debugger scope is the element to which the back trace will be reduced.
   *  Specifically this suppresses calls from inner functions called from that file.
   *  This is useful for DSL implementations.
   */
  void set_debugger_scope (const std::string &filename);

  /**
   *  @brief Removes the debugger scope
   */
  void remove_debugger_scope ();

  /**
   *  @brief Ignores the next exception
   *
   *  This is useful for suppressing reraised exceptions in the debugger.
   */
  void ignore_next_exception ();

  /**
   *  @brief Load the given file
   */
  void load_file (const std::string &filename);

  /**
   *  @brief Implementatiom of gsi::Interpreter::eval_string
   */
  void eval_string (const char *string, const char *filename = 0, int line = 1, int context = -1);

  /**
   *  @brief Implementatiom of gsi::Interpreter::eval_expr
   */
  tl::Variant eval_expr (const char *string, const char *filename = 0, int line = 1, int context = -1);
 
  /**
   *  @brief Implementatiom of gsi::Interpreter::eval_string_and_print
   */ 
  void eval_string_and_print (const char *string, const char *filename = 0, int line = 1, int context = -1);

  /**
   *  @brief Returns an inspector for the given context
   */
  virtual gsi::Inspector *inspector (int context = -1);

  /**
   *  @brief Defines a global variable with the given name and value 
   */
  void define_variable (const std::string &name, const std::string &value);

  /**
   *  @brief Gets a value indicating whether the interpreter is available
   */
  bool available () const;

  /**
   *  @brief Installs the given console for output
   */
  void push_console (gsi::Console *console);

  /**
   *  @brief Removes the given console
   */
  void remove_console (gsi::Console *console);

  /**
   *  @brief Installs the given execution handler
   *
   *  The execution handler is informed when the interpreter enters code execution (also
   *  from the outside, i.e. a method reimplementing a C++ method or a event handler).
   *  During execution, the handler receives trace events which allow him to intercept
   *  execution.
   */
  void push_exec_handler (gsi::ExecutionHandler *exec_handler);

  /**
   *  @brief Removes the given execution handler
   */
  void remove_exec_handler (gsi::ExecutionHandler *exec_handler);

  /**
   *  @brief Fetch the version string
   *
   *  Returns an empty string when no Python interpreter is installed.
   */
  std::string version () const;

  /**
   *  @brief Returns additional Python-specific documentation for the given method
   *  If no specific documentation exists, an empty string is returned.
   */
  std::string python_doc (const gsi::MethodBase *) const
  {
    return std::string ();
  }

  /**
   *  @brief Provide a first (basic) initialization
   */
  static void initialize ();

  /**
   *  @brief Always returns 0 
   */
  static PythonInterpreter *instance ();

};

}

#endif

#endif

