
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


#include "layApplication.h"
#include "layMainWindow.h"
#include "gsiDecl.h"
#include "gsiDeclQtExternal.h"

//  Import Qt bindings for QApplication
QT_EXTERNAL (QApplication)

namespace gsi
{

/** 
 *  @brief Makes the application crash (for testing the crash handler)
 */
void crash_me (int reason)
{
  union {
    void (*f_ptr)(int);
    char *c_ptr;
    const char *cc_ptr;
  } ugly_cast;

  if (reason == 0) {
    //  SIGABRT
    abort ();
  } else if (reason == 1) {
    //  SIGSEGV
    ugly_cast.c_ptr = 0;
    *ugly_cast.c_ptr = 0;
  } else if (reason == 2) {
    //  SIGILL
    //  NOTE: this triggers an illegal instruction on X86_64
    ugly_cast.cc_ptr = "abcd\0\0\0\0";
    (*ugly_cast.f_ptr) (0);
  } else if (reason == 3) {
    //  SIGFPE
    double x = -1.0;
    printf ("%g", sqrt (x));
  }
}

Class<lay::Application> decl_Application (QT_EXTERNAL_BASE (QApplication) "Application",
  
  method ("instance", &lay::Application::instance, 
    "@brief Return the singleton instance of the application\n"
    "\n"
    "There is exactly one instance of the application. This instance can be obtained with this "
    "method."
  ) +
  method ("crash_me", &crash_me, "@hide") +
  method ("symname", &lay::Application::symbol_name_from_address, "@hide") + 
  method ("is_editable?", &lay::Application::is_editable, 
    "@brief Return true if the application is in editable mode\n"
  ) +
  method ("get_config", &lay::Application::get_config,
    "@brief Query a configuration parameter\n"
    "\n"
    "@args name\n"
    "@param name The name of the configuration parameter whose value shall be obtained (a string)\n"
    "\n"
    "@return The value of the parameter\n"
    "\n"
    "This method returns the value of the given configuration parameter. If the parameter is not "
    "known, an exception will be thrown. Use \\get_config_names to obtain a list of all configuration "
    "parameter names available.\n"
    "\n"
    "Configuration parameters are always stored as strings. The actual format of this string is specific "
    "to the configuration parameter. The values delivered by this method correspond to the values stored "
    "in the configuration file "
  ) +
  method ("get_config_names", &lay::Application::get_config_names,
    "@brief Query the configuration parameter names\n"
    "\n"
    "@return A list of configuration parameter names\n"
    "\n"
    "This method returns the names of all known configuration parameters. These names can be used to "
    "get and set configuration parameter values."
  ) +
  method ("set_config", &lay::Application::set_config,
    "@brief Set a configuration parameter with the given name to the given value\n"
    "\n"
    "@args name, value\n"
    "@param name The name of the configuration parameter to set\n"
    "@param value The value to which to set the configuration parameter\n"
    "\n"
    "This method sets the configuration parameter with the given name to the given value. "
    "Values can only be strings. Numerical values have to be converted into strings first. "
    "The actual format of the value depends on the configuration parameter. The name must "
    "be one of the names returned by \\get_config_names."
    "\n"
    "It is possible to write an arbitrary name/value pair into the configuration database which then is "
    "written to the configuration file."
  ) +
  method ("write_config", &lay::Application::write_config,
    "@brief Write configuration to a file\n"
    "@args file_name\n"
    "\n"
    "If the configuration file cannot be written, \n"
    "is returned but no exception is thrown.\n"
  ) +
  method ("read_config", &lay::Application::read_config,
    "@brief Read the configuration from a file\n"
    "@args file_name\n"
    "\n"
    "This method siletly does nothing, if the config file does not\n"
    "exist. If it does and an error occured, the error message is printed\n"
    "on stderr. In both cases, false is returned.\n"
  ) +
  method ("main_window", &lay::Application::main_window,
    "@brief Return a reference to the main window\n"
    "\n"
    "@return A object reference to the main window object."
  ) +
  method ("execute|#exec", &lay::Application::exec,
    "@brief Execute the application's main loop\n"
    "\n"
    "This method must be called in order to execute the application in the main "
    "script if a script is provided."
  ) +
  method ("process_events", (void (lay::Application::*)()) &lay::Application::process_events,
    "@brief Process pending events\n"
    "\n"
    "This method processes pending events and dispatches them internally. Calling this "
    "method periodically during a long operation keeps the application 'alive'"
  ) + 
  method ("application_data_path", &lay::Application::appdata_path,
    "@brief Return the application's data path (where the configuration file is stored for example)\n"
    "\n"
    "This method has been added in version 0.22."
  ) +
  method ("inst_path", &lay::Application::inst_path,
    "@brief Return the application's installation path (where the executable is located)\n"
    "\n"
    "This method has been added in version 0.18. Version 0.22 offers the method \\klayout_path which "
    "delivers all components of the search path."
  ) +
  method ("klayout_path", &lay::Application::klayout_path,
    "@brief Return the KLayout path (search path for KLayout components)\n"
    "\n"
    "The result is an array containing the components of the path.\n"
    "\n"
    "This method has been added in version 0.22."
  ) +
  method ("exit", &lay::Application::exit,
    "@args result\n"
    "@brief Exit the application with the given exit status\n"
    "\n"
    "This method should be called instead of simply shutting down the process. It performs some "
    "important cleanup without which the process might crash. If the result code is 0 (success), "
    "the configuration file will be updated unless that has been disabled by the -nc command line switch."
    "\n"
    "This method has been added in version 0.22."
  ) + 
  method ("version", &lay::Application::version,
    "@brief Return the application's version string\n"
  ),

  "@brief The application object\n"
  "\n"
  "The application object is the main port from which to access all the internals "
  "of the application, in particular the main window."

);

}

