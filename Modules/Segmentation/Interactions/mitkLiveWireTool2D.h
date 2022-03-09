/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/

#ifndef mitkLiveWireTool2D_h
#define mitkLiveWireTool2D_h

#include <mitkEditableContourTool.h>
#include <mitkContourModelLiveWireInteractor.h>

namespace mitk
{
  /**
    \brief A 2D segmentation tool based on a LiveWire approach.

    The contour between the last point and the current mouse position is
    computed by searching the shortest path according to specific features of
    the image. The contour thus tends to snap to the boundary of objects.

    The tool always assumes that unconfirmed contours are always defined for the
    current time point. So the time step in which the contours will be stored as
    segmentations will be determined when the contours got confirmed. Then they
    will be transfered to the slices of the currently selected time step.
    Changing the time point/time step while tool is active will updated the working
    slice the live wire filter. So the behavior of the active live wire contour is
    always WYSIWYG (What you see is what you get).

    \sa SegTool2D
    \sa ImageLiveWireContourModelFilter

    \ingroup Interaction
    \ingroup ToolManagerEtAl

    \warning Only to be instantiated by mitk::ToolManager.
  */
  class MITKSEGMENTATION_EXPORT LiveWireTool2D : public EditableContourTool
  {
  public:
    mitkClassMacro(LiveWireTool2D, SegTool2D);
    itkFactorylessNewMacro(Self);

    us::ModuleResource GetCursorIconResource() const override;
    us::ModuleResource GetIconResource() const override;
    const char *GetName() const override;
    const char **GetXPM() const override;

    void SetSnapClosureContour(bool snap);

  protected:
    LiveWireTool2D();
    ~LiveWireTool2D() override;

    void ConnectActionsAndFunctions() override;

    void UpdateLiveWireContour();
    void OnTimePointChanged() override;

  private:
    /// \brief Initialize tool.
    void OnInitContour(StateMachineAction *, InteractionEvent *interactionEvent) override;

    /// \brief Add a control point and finish current segment.
    void OnAddPoint(StateMachineAction *, InteractionEvent *interactionEvent) override;

    /// \brief Draw a contour according to the mouse movement when mouse button is pressed and mouse is moved.
    void OnDrawing(StateMachineAction *, InteractionEvent *interactionEvent) override;

    void OnEndDrawing(StateMachineAction *, InteractionEvent *interactionEvent) override;

    /// \brief Actual LiveWire computation.
    void OnMouseMoved(StateMachineAction *, InteractionEvent *interactionEvent) override;

    /// \brief Check double click on first control point to finish the LiveWire tool.
    bool OnCheckPoint(const InteractionEvent *interactionEvent) override;

    /// \brief Finish LiveWire tool.
    void OnFinish(StateMachineAction *, InteractionEvent *interactionEvent) override;

    /// \brief Don't use dynamic cost map for LiveWire calculation.
    void OnMouseMoveNoDynamicCosts(StateMachineAction *, InteractionEvent *interactionEvent);

    /// \brief Finish contour interaction.
    void FinishTool() override;

    void EnableContourInteraction(bool on) override;

    void ReleaseInteractors() override;

    template <typename TPixel, unsigned int VImageDimension>
    void FindHighestGradientMagnitudeByITK(itk::Image<TPixel, VImageDimension> *inputImage,
                                           itk::Index<3> &index,
                                           itk::Index<3> &returnIndex);

    void UpdateClosureContour(mitk::Point3D endpoint) override;

    bool m_SnapClosureContour;

    mitk::ContourModelLiveWireInteractor::Pointer m_ContourInteractor;

    mitk::ImageLiveWireContourModelFilter::Pointer m_LiveWireFilter;
    mitk::ImageLiveWireContourModelFilter::Pointer m_LiveWireFilterClosure;

    bool m_CreateAndUseDynamicCosts;

    std::vector<mitk::ContourModelLiveWireInteractor::Pointer> m_LiveWireInteractors;
  };
}

#endif
