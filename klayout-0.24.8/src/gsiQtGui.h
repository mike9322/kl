
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


#ifndef _HDR_gsiQtGui
#define _HDR_gsiQtGui

#include "gsiQt.h"

#include <QtGui/QAbstractButton>
#include <QtGui/QAbstractGraphicsShapeItem>
#include <QtGui/QAbstractItemDelegate>
#include <QtGui/QAbstractItemView>
#include <QtGui/QAbstractPrintDialog>
#include <QtGui/QAbstractProxyModel>
#include <QtGui/QAbstractScrollArea>
#include <QtGui/QAbstractSlider>
#include <QtGui/QAbstractSpinBox>
#include <QtGui/QAbstractTextDocumentLayout>
#include <QtGui/QAccessible>
#include <QtGui/QAccessibleBridge>
#include <QtGui/QAccessibleBridgePlugin>
#include <QtGui/QAccessibleEvent>
#include <QtGui/QAccessibleInterface>
#include <QtGui/QAccessibleObject>
#include <QtGui/QAccessiblePlugin>
#include <QtGui/QAccessibleWidget>
#include <QtGui/QAction>
#include <QtGui/QActionEvent>
#include <QtGui/QActionGroup>
#include <QtGui/QApplication>
#include <QtGui/QBitmap>
#include <QtGui/QBoxLayout>
#include <QtGui/QBrush>
#include <QtGui/QButtonGroup>
#include <QtGui/QCDEStyle>
#include <QtGui/QCalendarWidget>
#include <QtGui/QCheckBox>
#include <QtGui/QCleanlooksStyle>
#include <QtGui/QClipboard>
#include <QtGui/QCloseEvent>
#include <QtGui/QColor>
#include <QtGui/QColorDialog>
#include <QtGui/QColorGroup>
#include <QtGui/QColormap>
#include <QtGui/QColumnView>
#include <QtGui/QComboBox>
#include <QtGui/QCommandLinkButton>
#include <QtGui/QCommonStyle>
#include <QtGui/QCompleter>
#include <QtGui/QConicalGradient>
#include <QtGui/QContextMenuEvent>
#include <QtGui/QCopChannel>
#include <QtGui/QCursor>
#include <QtGui/QDataWidgetMapper>
#include <QtGui/QDateEdit>
#include <QtGui/QDateTimeEdit>
#include <QtGui/QDecoration>
#include <QtGui/QDecorationDefault>
#include <QtGui/QDecorationFactory>
#include <QtGui/QDecorationPlugin>
#include <QtGui/QDesktopServices>
#include <QtGui/QDesktopWidget>
#include <QtGui/QDial>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QDirModel>
#include <QtGui/QDirectPainter>
#include <QtGui/QDockWidget>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QDoubleValidator>
#include <QtGui/QDrag>
#include <QtGui/QDragEnterEvent>
#include <QtGui/QDragLeaveEvent>
#include <QtGui/QDragMoveEvent>
#include <QtGui/QDropEvent>
#include <QtGui/QErrorMessage>
#include <QtGui/QFileDialog>
#include <QtGui/QFileIconProvider>
#include <QtGui/QFileOpenEvent>
#include <QtGui/QFileSystemModel>
#include <QtGui/QFocusEvent>
#include <QtGui/QFocusFrame>
#include <QtGui/QFont>
#include <QtGui/QFontComboBox>
#include <QtGui/QFontDatabase>
#include <QtGui/QFontDialog>
#include <QtGui/QFontEngineInfo>
#include <QtGui/QFontEnginePlugin>
#include <QtGui/QFontInfo>
#include <QtGui/QFontMetrics>
#include <QtGui/QFontMetricsF>
#include <QtGui/QFormLayout>
#include <QtGui/QFrame>
#include <QtGui/QGenericMatrix>
#include <QtGui/QGesture>
#include <QtGui/QGestureEvent>
#include <QtGui/QGestureRecognizer>
#include <QtGui/QGradient>
#include <QtGui/QGraphicsAnchor>
#include <QtGui/QGraphicsAnchorLayout>
#include <QtGui/QGraphicsBlurEffect>
#include <QtGui/QGraphicsColorizeEffect>
#include <QtGui/QGraphicsDropShadowEffect>
#include <QtGui/QGraphicsEffect>
#include <QtGui/QGraphicsEllipseItem>
#include <QtGui/QGraphicsGridLayout>
#include <QtGui/QGraphicsItem>
#include <QtGui/QGraphicsItemAnimation>
#include <QtGui/QGraphicsItemGroup>
#include <QtGui/QGraphicsLayout>
#include <QtGui/QGraphicsLayoutItem>
#include <QtGui/QGraphicsLineItem>
#include <QtGui/QGraphicsLinearLayout>
#include <QtGui/QGraphicsObject>
#include <QtGui/QGraphicsOpacityEffect>
#include <QtGui/QGraphicsPathItem>
#include <QtGui/QGraphicsPixmapItem>
#include <QtGui/QGraphicsPolygonItem>
#include <QtGui/QGraphicsProxyWidget>
#include <QtGui/QGraphicsRectItem>
#include <QtGui/QGraphicsRotation>
#include <QtGui/QGraphicsScale>
#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsSceneContextMenuEvent>
#include <QtGui/QGraphicsSceneDragDropEvent>
#include <QtGui/QGraphicsSceneEvent>
#include <QtGui/QGraphicsSceneHelpEvent>
#include <QtGui/QGraphicsSceneHoverEvent>
#include <QtGui/QGraphicsSceneMouseEvent>
#include <QtGui/QGraphicsSceneMoveEvent>
#include <QtGui/QGraphicsSceneResizeEvent>
#include <QtGui/QGraphicsSceneWheelEvent>
#include <QtGui/QGraphicsSimpleTextItem>
#include <QtGui/QGraphicsTextItem>
#include <QtGui/QGraphicsTransform>
#include <QtGui/QGraphicsView>
#include <QtGui/QGraphicsWidget>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QGtkStyle>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QHelpEvent>
#include <QtGui/QHideEvent>
#include <QtGui/QHoverEvent>
#include <QtGui/QIcon>
#include <QtGui/QIconDragEvent>
#include <QtGui/QIconEngine>
#include <QtGui/QIconEnginePlugin>
#include <QtGui/QIconEnginePluginV2>
#include <QtGui/QIconEngineV2>
#include <QtGui/QImage>
#include <QtGui/QImageTextKeyLang>
#include <QtGui/QImageIOHandler>
#include <QtGui/QImageIOPlugin>
#include <QtGui/QImageReader>
#include <QtGui/QImageWriter>
#include <QtGui/QInputContext>
#include <QtGui/QInputContextFactory>
#include <QtGui/QInputContextPlugin>
#include <QtGui/QInputDialog>
#include <QtGui/QInputEvent>
#include <QtGui/QInputMethodEvent>
#include <QtGui/QIntValidator>
#include <QtGui/QItemDelegate>
#include <QtGui/QItemEditorCreator>
#include <QtGui/QItemEditorCreatorBase>
#include <QtGui/QItemEditorFactory>
#include <QtGui/QItemSelection>
#include <QtGui/QItemSelectionModel>
#include <QtGui/QItemSelectionRange>
#include <QtGui/QKbdDriverFactory>
#include <QtGui/QKbdDriverPlugin>
#include <QtGui/QKeyEvent>
#include <QtGui/QKeyEventTransition>
#include <QtGui/QKeySequence>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QLayout>
#include <QtGui/QLayoutItem>
#include <QtGui/QLineEdit>
#include <QtGui/QLinearGradient>
#include <QtGui/QListView>
#include <QtGui/QListWidget>
#include <QtGui/QListWidgetItem>
#include <QtGui/QMacCocoaViewContainer>
#include <QtGui/QMacNativeWidget>
#include <QtGui/QMacPasteboardMime>
#include <QtGui/QMatrix>
#include <QtGui/QMatrix4x4>
#include <QtGui/QMainWindow>
#include <QtGui/QMdiArea>
#include <QtGui/QMdiSubWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QMenuItem>
#include <QtGui/QMessageBox>
#include <QtGui/QMotifStyle>
#include <QtGui/QMouseEvent>
#include <QtGui/QMoveEvent>
#include <QtGui/QMovie>
#include <QtGui/QPageSetupDialog>
#include <QtGui/QPaintDevice>
#include <QtGui/QPaintEngine>
#include <QtGui/QPaintEngineState>
#include <QtGui/QPaintEvent>
#include <QtGui/QPainter>
#include <QtGui/QPainterPath>
#include <QtGui/QPainterPathStroker>
#include <QtGui/QPalette>
#include <QtGui/QPen>
#include <QtGui/QPicture>
#include <QtGui/QPixmap>
#include <QtGui/QPixmapCache>
#include <QtGui/QPlainTextDocumentLayout>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPlastiqueStyle>
#include <QtGui/QPolygon>
#include <QtGui/QPolygonF>
#include <QtGui/QPrintDialog>
#include <QtGui/QPrintEngine>
#include <QtGui/QPrintPreviewDialog>
#include <QtGui/QPrintPreviewWidget>
#include <QtGui/QPrinter>
#include <QtGui/QPrinterInfo>
#include <QtGui/QProgressBar>
#include <QtGui/QProgressDialog>
#include <QtGui/QPushButton>
#include <QtGui/QRadialGradient>
#include <QtGui/QRadioButton>
#include <QtGui/QRegExpValidator>
#include <QtGui/QRegion>
#include <QtGui/QResizeEvent>
#include <QtGui/QRubberBand>
#include <QtGui/QScrollArea>
#include <QtGui/QScrollBar>
#include <QtGui/QSessionManager>
#include <QtGui/QShortcut>
#include <QtGui/QShortcutEvent>
#include <QtGui/QShowEvent>
#include <QtGui/QSizeGrip>
#include <QtGui/QSizePolicy>
#include <QtGui/QSlider>
#include <QtGui/QSortFilterProxyModel>
#include <QtGui/QSound>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QSplashScreen>
#include <QtGui/QSplitter>
#include <QtGui/QSplitterHandle>
#include <QtGui/QStackedLayout>
#include <QtGui/QStackedWidget>
#include <QtGui/QStandardItem>
#include <QtGui/QStandardItemEditorCreator>
#include <QtGui/QStandardItemModel>
#include <QtGui/QStatusBar>
#include <QtGui/QStatusTipEvent>
#include <QtGui/QStringListModel>
#include <QtGui/QStyle>
#include <QtGui/QStyleFactory>
#include <QtGui/QStyleHintReturn>
#include <QtGui/QStyleHintReturnMask>
#include <QtGui/QStyleHintReturnVariant>
#include <QtGui/QStyleOption>
#include <QtGui/QStyleOptionButton>
#include <QtGui/QStyleOptionComboBox>
#include <QtGui/QStyleOptionComplex>
#include <QtGui/QStyleOptionDockWidget>
#include <QtGui/QStyleOptionFocusRect>
#include <QtGui/QStyleOptionFrame>
#include <QtGui/QStyleOptionFrameV2>
#include <QtGui/QStyleOptionFrameV3>
#include <QtGui/QStyleOptionGraphicsItem>
#include <QtGui/QStyleOptionGroupBox>
#include <QtGui/QStyleOptionHeader>
#include <QtGui/QStyleOptionMenuItem>
#include <QtGui/QStyleOptionProgressBar>
#include <QtGui/QStyleOptionProgressBarV2>
#include <QtGui/QStyleOptionQ3DockWindow>
#include <QtGui/QStyleOptionQ3ListView>
#include <QtGui/QStyleOptionQ3ListViewItem>
#include <QtGui/QStyleOptionRubberBand>
#include <QtGui/QStyleOptionSizeGrip>
#include <QtGui/QStyleOptionSlider>
#include <QtGui/QStyleOptionSpinBox>
#include <QtGui/QStyleOptionTab>
#include <QtGui/QStyleOptionTabBarBase>
#include <QtGui/QStyleOptionTabBarBaseV2>
#include <QtGui/QStyleOptionTabV2>
#include <QtGui/QStyleOptionTabV3>
#include <QtGui/QStyleOptionTabWidgetFrame>
#include <QtGui/QStyleOptionTitleBar>
#include <QtGui/QStyleOptionToolBar>
#include <QtGui/QStyleOptionToolBox>
#include <QtGui/QStyleOptionToolBoxV2>
#include <QtGui/QStyleOptionToolButton>
#include <QtGui/QStyleOptionViewItem>
#include <QtGui/QStyleOptionViewItemV2>
#include <QtGui/QStyleOptionViewItemV3>
#include <QtGui/QStyleOptionViewItemV4>
#include <QtGui/QStylePainter>
#include <QtGui/QStylePlugin>
#include <QtGui/QStyledItemDelegate>
#include <QtGui/QSyntaxHighlighter>
#include <QtGui/QSystemTrayIcon>
#include <QtGui/QTabBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTableView>
#include <QtGui/QTableWidget>
#include <QtGui/QTableWidgetItem>
#include <QtGui/QTableWidgetSelectionRange>
#include <QtGui/QTabletEvent>
#include <QtGui/QTextBlock>
#include <QtGui/QTextBlockFormat>
#include <QtGui/QTextBlockGroup>
#include <QtGui/QTextBlockUserData>
#include <QtGui/QTextBrowser>
#include <QtGui/QTextCharFormat>
#include <QtGui/QTextCursor>
#include <QtGui/QTextDocument>
#include <QtGui/QTextDocumentFragment>
#include <QtGui/QTextDocumentWriter>
#include <QtGui/QTextEdit>
#include <QtGui/QTextFormat>
#include <QtGui/QTextFragment>
#include <QtGui/QTextFrame>
#include <QtGui/QTextFrameFormat>
#include <QtGui/QTextImageFormat>
#include <QtGui/QTextInlineObject>
#include <QtGui/QTextItem>
#include <QtGui/QTextLayout>
#include <QtGui/QTextLength>
#include <QtGui/QTextLine>
#include <QtGui/QTextList>
#include <QtGui/QTextListFormat>
#include <QtGui/QTextObject>
#include <QtGui/QTextObjectInterface>
#include <QtGui/QTextOption>
#include <QtGui/QTextTable>
#include <QtGui/QTextTableCell>
#include <QtGui/QTextTableCellFormat>
#include <QtGui/QTextTableFormat>
#include <QtGui/QTimeEdit>
#include <QtGui/QToolBar>
#include <QtGui/QToolBox>
#include <QtGui/QToolButton>
#include <QtGui/QToolTip>
#include <QtGui/QTransform>
#include <QtGui/QTreeView>
#include <QtGui/QTreeWidget>
#include <QtGui/QTreeWidgetItem>
#include <QtGui/QTreeWidgetItemIterator>
#include <QtGui/QUndoCommand>
#include <QtGui/QUndoGroup>
#include <QtGui/QUndoStack>
#include <QtGui/QUndoView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QValidator>
#include <QtGui/QVector2D>
#include <QtGui/QVector3D>
#include <QtGui/QVector4D>
#include <QtGui/QValidator>
#include <QtGui/QWhatsThis>
#include <QtGui/QWhatsThisClickedEvent>
#include <QtGui/QWheelEvent>
#include <QtGui/QWidget>
#include <QtGui/QWidgetAction>
#include <QtGui/QWidgetItem>
#include <QtGui/QWindowStateChangeEvent>
#include <QtGui/QWindowsMime>
#include <QtGui/QWindowsStyle>
#include <QtGui/QWizard>
#include <QtGui/QWizardPage>
  
namespace qt_gsi
{

#ifdef _WIN32

template <>
struct Converter<WId>
{
public:
  typedef WId source_type;
  typedef size_t target_type;
  static source_type toq (target_type c) { return source_type (c); }
  static target_type toc (source_type qc) { return target_type (qc); }
};

template <>
struct Converter<HCURSOR>
{
public:
  typedef HCURSOR source_type;
  typedef size_t target_type;
  static source_type toq (target_type c) { return source_type (c); }
  static target_type toc (source_type qc) { return target_type (qc); }
};

template <>
struct Converter<HFONT>
{
public:
  typedef HFONT source_type;
  typedef size_t target_type;
  static source_type toq (target_type c) { return source_type (c); }
  static target_type toc (source_type qc) { return target_type (qc); }
};

#endif

}

#endif

