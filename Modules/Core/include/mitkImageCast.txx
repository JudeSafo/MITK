/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/

#include <mitkImageAccessByItk.h>
#include <mitkImageCast.h>

#include <itkCastImageFilter.h>
#include <itkImage.h>

namespace mitk
{
#ifndef DOXYGEN_SKIP

  template <typename ItkOutputImageType>
  void CastToItkImage(const mitk::Image *mitkImage, itk::SmartPointer<ItkOutputImageType> &itkOutputImage)
  {
    AccessFixedDimensionByItk_1(mitkImage, _CastToItkImage2Access, ItkOutputImageType::ImageDimension, itkOutputImage);
  }

  template <typename TPixelType, unsigned int VImageDimension>
  void CastToItkImage(const mitk::Image *mitkImage,
                      itk::SmartPointer<itk::VectorImage<TPixelType, VImageDimension>> &itkOutputImage)
  {
    AccessVectorFixedDimensionByItk_n(mitkImage, _CastToItkImage2Access, VImageDimension, (itkOutputImage));
  }

  template <typename TPixel, unsigned int VImageDimension, class ItkOutputImageType>
  void _CastToItkImage2Access(const itk::Image<TPixel, VImageDimension> *itkInputImage,
                              itk::SmartPointer<ItkOutputImageType> &itkOutputImage)
  {
    typedef itk::Image<TPixel, VImageDimension> ItkInputImageType;
    if (typeid(ItkInputImageType) == typeid(ItkOutputImageType))
    {
      itkOutputImage = const_cast<ItkOutputImageType *>(reinterpret_cast<const ItkOutputImageType *>(itkInputImage));
      return;
    }
    typedef itk::CastImageFilter<ItkInputImageType, ItkOutputImageType> CastImageFilterType;
    typename CastImageFilterType::Pointer castImageFilter = CastImageFilterType::New();
    castImageFilter->SetInput(itkInputImage);
    castImageFilter->Update();
    itkOutputImage = castImageFilter->GetOutput();
  }

  template <typename TPixel, unsigned int VImageDimension, class ItkOutputImageType>
  void _CastToItkImage2Access(const itk::VectorImage<TPixel, VImageDimension> *itkInputImage,
                              itk::SmartPointer<ItkOutputImageType> &itkOutputImage)
  {
    typedef itk::VectorImage<TPixel, VImageDimension> ItkInputImageType;
    if (typeid(ItkInputImageType) == typeid(ItkOutputImageType))
    {
      itkOutputImage = const_cast<ItkOutputImageType *>(reinterpret_cast<const ItkOutputImageType *>(itkInputImage));
      return;
    }
    typedef itk::CastImageFilter<ItkInputImageType, ItkOutputImageType> CastImageFilterType;
    typename CastImageFilterType::Pointer castImageFilter = CastImageFilterType::New();
    castImageFilter->SetInput(itkInputImage);
    castImageFilter->Update();
    itkOutputImage = castImageFilter->GetOutput();
  }

#endif // DOXYGEN_SKIP
}
