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

#ifndef INIEDITOR_H
#define INIEDITOR_H

#include <iplugintool.h>

class IniEditor : public MOBase::IPluginTool
{
  Q_OBJECT
  Q_INTERFACES(MOBase::IPlugin MOBase::IPluginTool)

public:

  IniEditor();

  virtual bool init(MOBase::IOrganizer *moInfo);
  virtual QString name() const;
  virtual QString author() const;
  virtual QString description() const;
  virtual MOBase::VersionInfo version() const;
  virtual bool isActive() const;
  virtual QList<MOBase::PluginSetting> settings() const;

  virtual QString displayName() const;
  virtual QString tooltip() const;
  virtual QIcon icon() const;

public slots:
  virtual void display() const;

private:
  std::vector<QString> getIniFiles() const;

private:
  const MOBase::IOrganizer *m_MOInfo;
};

#endif // INIEDITOR_H
