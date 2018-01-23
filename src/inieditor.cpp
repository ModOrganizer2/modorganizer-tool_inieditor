/*
Copyright (C) 2012 Sebastian Herbord. All rights reserved.

This file is part of ini editor plugin for MO

Ini editor plugin is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Ini editor plugin is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Ini editor plugin.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "inieditor.h"

#include "iplugingame.h"
#include "textviewer.h"
#include <utility.h>
#include <imoinfo.h>

#include <QtPlugin>
#include <QMessageBox>
#include <QDir>
#include <QApplication>


using namespace MOBase;


IniEditor::IniEditor()
  : m_MOInfo(nullptr)
{
}

bool IniEditor::init(IOrganizer *moInfo)
{
  m_MOInfo = moInfo;
  return true;
}

QString IniEditor::name() const
{
  return "INI Editor";
}

QString IniEditor::author() const
{
  return "Tannin";
}

QString IniEditor::description() const
{
  return tr("Very basic editor for ini files");
}

VersionInfo IniEditor::version() const
{
  return VersionInfo(1, 0, 1, VersionInfo::RELEASE_FINAL);
}

bool IniEditor::isActive() const
{
  return true;
}

QList<PluginSetting> IniEditor::settings() const
{
  QList<PluginSetting> result;
  result.push_back(PluginSetting("external", "Use an external editor to open the files", QVariant(false)));
  result.push_back(PluginSetting("associated", "When using an external editor, use the application associated with \"ini\" files. "
                                 "If false, uses the \"edit\" command which usually invokes regular notepad.", QVariant(true)));
  return result;
}

QString IniEditor::displayName() const
{
  return tr("INI Editor");
}

QString IniEditor::tooltip() const
{
  return tr("Edit the ini file of the current profile");
}

QIcon IniEditor::icon() const
{
	return QIcon(":/inieditor/icon_document");
}

void IniEditor::display() const
{
	if (m_MOInfo == nullptr) {
		throw MyException(tr("plugin not initialized"));
	}

	QStringList iniFiles = m_MOInfo->managedGame()->iniFiles();
	if (m_MOInfo->pluginSetting(name(), "external").toBool()) {
		if (m_MOInfo->profile()->localSettingsEnabled())
		{
			for (QString const &file : iniFiles) {
				QString fileName = QString("%1/%3").arg(m_MOInfo->profile()->absolutePath())
					.arg(file);
				::ShellExecuteW(nullptr, m_MOInfo->pluginSetting(name(), "associated").toBool() ? L"open" : L"edit",
					ToWString(fileName).c_str(), nullptr, nullptr, SW_SHOWNORMAL);
			}
		}
		else {
			for (QString const &file : iniFiles) {
				QString fileName = QString("%1/%3").arg((m_MOInfo->managedGame()->documentsDirectory()).absolutePath())
					.arg(file);
				::ShellExecuteW(nullptr, m_MOInfo->pluginSetting(name(), "associated").toBool() ? L"open" : L"edit",
					ToWString(fileName).c_str(), nullptr, nullptr, SW_SHOWNORMAL);
			}
		}
	}
	else {
		TextViewer *viewer = new TextViewer("Ini Files", parentWidget());
		if (m_MOInfo->profile()->localSettingsEnabled())
		{
			viewer->setDescription(tr("Editing profile local INIs. Local game settings is Enabled."));
			for (QString const &file : iniFiles) {
				QString fileName = QString("%1/%3").arg(m_MOInfo->profile()->absolutePath())
					.arg(file);
				QFileInfo fileInfo(fileName);
				if (fileInfo.exists()) {
					if (fileInfo.size() < 1024 * 1024) {
						viewer->addFile(fileName, true);
					}
					else {
						QMessageBox::warning(parentWidget(), tr("File too big"),
							tr("Sorry, the file %1 is too large"
								" to be handled by the Ini Editor").arg(fileName));
					}
				}
			}
		}
		else {
			viewer->setDescription(tr("Editing global INIs (in mygames). Local game settings is Disabled."));
			for (QString const &file : iniFiles) {
				QString fileName = QString("%1/%3").arg((m_MOInfo->managedGame()->documentsDirectory()).absolutePath())
					.arg(file);
				QFileInfo fileInfo(fileName);
				if (fileInfo.exists()) {
					if (fileInfo.size() < 1024 * 1024) {
						viewer->addFile(fileName, true);
					}
					else {
						QMessageBox::warning(parentWidget(), tr("File too big"),
							tr("Sorry, the file %1 is too large"
								" to be handled by the Ini Editor").arg(fileName));
					}
				}
			}
		}
		viewer->show();
	}
}



#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
Q_EXPORT_PLUGIN2(iniEditor, IniEditor)
#endif
