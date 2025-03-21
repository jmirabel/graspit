//######################################################################
//
// GraspIt!
// Copyright (C) 2002-2009  Columbia University in the City of New York.
// All rights reserved.
//
// GraspIt! is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// GraspIt! is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with GraspIt!.  If not, see <http://www.gnu.org/licenses/>.
//
// Author(s): Andrew T. Miller
//
// $Id: graspitApp.cpp,v 1.5 2009/03/30 20:42:02 cmatei Exp $
//
//######################################################################

/*! \file
  \brief Implements GraspItApp, a subclass of QApplication.
*/

#include "graspit/graspitApp.h"
#include <QSettings>
#include <QLabel>
#include <QFrame>
#include <QDesktopWidget>

#include "graspit/mytools.h"

/*! A pointer to the splash screen, implemented as a QLabel. */
static QLabel *splash = 0;

/*!
  Reads the registry to determine the location of the main window, and whether
  or not to display the splash screen.  If so, it shows the GraspIt! logo
  splash screen in the center of the screen.
 */
void
GraspItApp::showSplash()
{
  QRect screen = QApplication::desktop()->screenGeometry();
  QSettings config;
  config.setPath(QSettings::IniFormat, QSettings::UserScope, "/Columbia");

  QRect mainRect;
  QString keybase = "/GraspIt/0.9/";
  bool show = config.value(keybase + "SplashScreen", TRUE).toBool();
  mainRect.setX(config.value(keybase + "Geometries/MainwindowX", 0).toInt());
  mainRect.setY(config.value(keybase + "Geometries/MainwindowY", 0).toInt());
  mainRect.setWidth(config.value(keybase + "Geometries/MainwindowWidth", 500).toInt());
  mainRect.setHeight(config.value(keybase + "Geometries/MainwindowHeight", 500).toInt());
  screen = QApplication::desktop()->screenGeometry(QApplication::desktop()->screenNumber(mainRect.center()));

  if (show) {
    splash = new QLabel("splash", 0, Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint | Qt::WindowStaysOnTopHint);
    // WStyle_Customize | WStyle_StaysOnTop
    splash->setAttribute(Qt::WA_DeleteOnClose, true);
    splash->setFrameStyle(QFrame::WinPanel | QFrame::Raised);
    splash->setPixmap(QPixmap(":/images/splash.jpg"));
    splash->adjustSize();
    splash->setFixedSize(splash->sizeHint());
    splash->setWindowTitle("GraspIt!");
    splash->move(screen.center() - QPoint(splash->width() / 2, splash->height() / 2));
    splash->show();
    QApplication::processEvents(QEventLoop::AllEvents, 1);
    //  set_splash_status( "Initializing..." );
  }
}

/*!
  Removes the splash screen, freeing its memory.
*/
void GraspItApp::closeSplash()
{
  if (splash) { delete splash; }
}
