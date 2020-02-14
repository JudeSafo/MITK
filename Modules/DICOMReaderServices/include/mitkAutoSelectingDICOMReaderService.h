/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/

#ifndef MITKAUTOSELECTINGDICOMREADERSERVICE_H
#define MITKAUTOSELECTINGDICOMREADERSERVICE_H

#include <mitkBaseDICOMReaderService.h>

namespace mitk {

  /**
  Service wrapper that auto selects (using the mitk::DICOMFileReaderSelector) the best DICOMFileReader from
  the DICOMReader module.
  */
class AutoSelectingDICOMReaderService : public BaseDICOMReaderService
{
public:
  AutoSelectingDICOMReaderService();

protected:
  /** Returns the reader instance that should be used. The descission may be based
  * one the passed relevant file list.*/
  mitk::DICOMFileReader::Pointer GetReader(const mitk::StringList& relevantFiles) const override;

private:

  AutoSelectingDICOMReaderService* Clone() const override;
};

}

#endif // MITKDICOMSERIESREADERSERVICE_H
