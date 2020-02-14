/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/

#ifndef QMITKDATASTORAGEVIEWERTESTVIEW_H
#define QMITKDATASTORAGEVIEWERTESTVIEW_H

// mitk gui qt common plugin
#include <QmitkAbstractView.h>
#include "QmitkModelViewSelectionConnector.h"
#include "QmitkSelectionServiceConnector.h"

// data storage viewer test plugin
#include "ui_QmitkDataStorageViewerTestControls.h"

// qt widgets module
#include "QmitkDataStorageDefaultListModel.h"

/**
* @brief DataStorageViewerTestView
*/
class QmitkDataStorageViewerTestView : public QmitkAbstractView
{
  Q_OBJECT

public:

  static const std::string VIEW_ID;

protected:

  void SetFocus() override;

  void CreateQtPartControl(QWidget* parent) override;

private Q_SLOTS:

  void SetAsSelectionProvider1(bool checked);
  void SetAsSelectionProvider2(bool checked);
  void SetAsSelectionProvider3(bool checked);
  void SetAsSelectionProvider4(bool checked);
  void SetAsSelectionListener1(bool checked);
  void SetAsSelectionListener2(bool checked);
  void SetAsSelectionListener3(bool checked);
  void SetAsSelectionListener4(bool checked);

  void OnOnlyImages(bool checked);
  void OnOnlyImages2(bool checked);
  void OnOnlyUneven(bool checked);

private:

  Ui::QmitkDataStorageViewerTestControls m_Controls;
  QmitkDataStorageDefaultListModel* m_DataStorageDefaultListModel;
  QmitkDataStorageDefaultListModel* m_DataStorageDefaultListModel2;

  std::unique_ptr<QmitkModelViewSelectionConnector> m_ModelViewSelectionConnector;
  std::unique_ptr<QmitkSelectionServiceConnector> m_SelectionServiceConnector;
  std::unique_ptr<QmitkModelViewSelectionConnector> m_ModelViewSelectionConnector2;
  std::unique_ptr<QmitkSelectionServiceConnector> m_SelectionServiceConnector2;

  std::unique_ptr<QmitkSelectionServiceConnector> m_SelectionServiceConnector3;
  std::unique_ptr<QmitkSelectionServiceConnector> m_SelectionServiceConnector4;
};

#endif // QMITKDATASTORAGEVIEWERTESTVIEW_H
