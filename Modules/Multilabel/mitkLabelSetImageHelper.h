/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/

#ifndef MITKLABELSETIMAGEHELPER_H
#define MITKLABELSETIMAGEHELPER_H

#include <MitkMultilabelExports.h>

#include <mitkDataNode.h>
#include <mitkLabelSetImage.h>

namespace mitk
{
  /**
   *
   */
  namespace LabelSetImageHelper
  {
    /**
     * @brief This function creates and returns a new data node containing the given image as data.
     *        The segmentation node is named according to the given reference data node.
     *        Some properties are set to automatically link the segmentation node with its parent node.
     *
     * @param referenceNode             The reference node from which the name of the new segmentation node
     *                                  is derived.
     * @param initialSegmentationImage  The segmentation image that is used to initialize the label set image.
     * @param segmentationName          An optional name for the new segmentation node.
     *
     * @return                          The new segmentation node as a data node pointer.
     */
    MITKMULTILABEL_EXPORT mitk::DataNode::Pointer CreateNewSegmentationNode(const DataNode* referenceNode,
      const Image* initialSegmentationImage = nullptr, const std::string& segmentationName = std::string());

    /**
     * @brief This function creates and returns a new label. The label is automatically assigned a
     *        label name, depending on the current number of labels of the active label set of the
     *        given label set image.
     *        The color of the label is derived from the MULTILABEL lookup table, depending on the
     *        number of labels.
     *
     * @param labelSetImage   The label set image from which the number of labels of the active label
     *                        set is derived.
     *
     * @return                The new labe as a pointer.
     */
    MITKMULTILABEL_EXPORT mitk::Label::Pointer CreateNewLabel(const LabelSetImage* labelSetImage);

  } // namespace LabelSetImageHelper
} // namespace mitk

#endif // MITKLABELSETIMAGEHELPER_H
