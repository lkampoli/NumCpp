#include"NumC.hpp"

#include<string>
#include<iostream>

#ifndef BOOST_PYTHON_STATIC_LIB
#define BOOST_PYTHON_STATIC_LIB    
#endif

#ifndef BOOST_NUMPY_STATIC_LIB
#define BOOST_NUMPY_STATIC_LIB    
#endif

#include "boost/python.hpp"
#include "boost/python/suite/indexing/vector_indexing_suite.hpp" // needed for returning a std::vector directly
#include "boost/python/return_internal_reference.hpp" // needed for returning references and pointers
#include "boost/python/numpy.hpp" // needed for working with numpy 
// i don't know why, but google said these are needed to fix a linker error i was running into for numpy. 
#define BOOST_LIB_NAME "boost_numpy3"
#include "boost/config/auto_link.hpp"

namespace bp = boost::python;
namespace np = boost::python::numpy;

using namespace NumC;

//================================================================================

namespace ShapeInterface
{
    bool testListContructor()
    {
        Shape test = { 357, 666 };
        if (test.rows == 357 && test.cols == 666)
        {
            return true;
        }

        return false;
    }
}

//================================================================================

namespace NdArrayInterface
{
    template<typename dtype>
    bool test1DListContructor()
    {
        NdArray<dtype> test = { 1,2,3,4,666,357,314159 };
        if (test.size() != 7)
        {
            return false;
        }

        if (test.shape().rows != 1 || test.shape().cols != test.size())
        {
            return false;
        }

        return test[0] == 1 && test[1] == 2 && test[2] == 3 && test[3] == 4 && test[4] == 666 && test[5] == 357 && test[6] == 314159;
    }

    //================================================================================

    template<typename dtype>
    bool test2DListContructor()
    {
        NdArray<dtype> test = { {1,2}, {4,666}, {314159, 9}, {0, 8} };
        if (test.size() != 8)
        {
            return false;
        }

        if (test.shape().rows != 4 || test.shape().cols != 2)
        {
            return false;
        }

        return test[0] == 1 && test[1] == 2 && test[2] == 4 && test[3] == 666 && test[4] == 314159 && test[5] == 9 && test[6] == 0 && test[7] == 8;
    }

    //================================================================================

    template<typename dtype>
    np::ndarray getNumpyArray(const NdArray<dtype>& inArray)
    {
        return numCToBoost(inArray);
    }

    //================================================================================

    template<typename dtype>
    void setArray(NdArray<dtype>& self, np::ndarray& inBoostArray)
    {
        BoostNdarrayHelper newNdArrayHelper(&inBoostArray);
        uint8 numDims = newNdArrayHelper.numDimensions();
        if (numDims > 2)
        {
            std::string errorString = "ERROR: Input array can only have up to 2 dimensions!";
            PyErr_SetString(PyExc_RuntimeError, errorString.c_str());
        }

        self = boostToNumC<dtype>(inBoostArray);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray all(NdArray<dtype>& self, Axis::Type inAxis = Axis::NONE)
    {
        return numCToBoost(self.all(inAxis));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray any(NdArray<dtype>& self, Axis::Type inAxis = Axis::NONE)
    {
        return numCToBoost(self.any(inAxis));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray argmax(NdArray<dtype>& self, Axis::Type inAxis = Axis::NONE)
    {
        return numCToBoost(self.argmax(inAxis));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray argmin(NdArray<dtype>& self, Axis::Type inAxis = Axis::NONE)
    {
        return numCToBoost(self.argmin(inAxis));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray argsort(NdArray<dtype>& self, Axis::Type inAxis = Axis::NONE)
    {
        return numCToBoost(self.argsort(inAxis));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray clip(NdArray<dtype>& self, dtype inMin, dtype inMax)
    {
        return numCToBoost(self.clip(inMin, inMax));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray copy(NdArray<dtype>& self)
    {
        return numCToBoost(self.copy());
    }

    //================================================================================

    template<typename dtype>
    np::ndarray contains(NdArray<dtype>& self, dtype inValue, Axis::Type inAxis = Axis::NONE)
    {
        return numCToBoost(self.contains(inValue, inAxis));
    }

    //================================================================================

    template<typename dtype, typename dtypeOut>
    np::ndarray cumprod(NdArray<dtype>& self, Axis::Type inAxis = Axis::NONE)
    {
        return numCToBoost(self.cumprod<dtypeOut>(inAxis));
    }

    //================================================================================

    template<typename dtype, typename dtypeOut>
    np::ndarray cumsum(NdArray<dtype>& self, Axis::Type inAxis = Axis::NONE)
    {
        return numCToBoost(self.cumsum<dtypeOut>(inAxis));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray diagonal(NdArray<dtype>& self, uint32 inOffset = 0, Axis::Type inAxis = Axis::ROW)
    {
        return numCToBoost(self.diagonal(inOffset, inAxis));
    }

    //================================================================================

    template<typename dtype, typename dtypeOut>
    np::ndarray dot(NdArray<dtype>& self, NdArray<dtype>& inOtherArray)
    {
        return numCToBoost(self.dot<dtypeOut>(inOtherArray));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray fill(NdArray<dtype>& self, dtype inFillValue)
    {
        self.fill(inFillValue);
        return numCToBoost(self);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray flatten(NdArray<dtype>& self)
    {
        return numCToBoost(self.flatten());
    }

    //================================================================================

    template<typename dtype>
    dtype getValueFlat(NdArray<dtype>& self, int32 inIndex)
    {
        return self.at(inIndex);
    }

    //================================================================================

    template<typename dtype>
    dtype getValueRowCol(NdArray<dtype>& self, int32 inRow, int32 inCol)
    {
        return self.at(inRow, inCol);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray getSlice1D(NdArray<dtype>& self, const Slice& inSlice)
    {
        return numCToBoost(self.at(inSlice));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray getSlice2D(NdArray<dtype>& self, const Slice& inRowSlice, const Slice& inColSlice)
    {
        return numCToBoost(self.at(inRowSlice, inColSlice));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray getSlice2DCol(NdArray<dtype>& self, const Slice& inRowSlice, int32 inColIndex)
    {
        return numCToBoost(self.at(inRowSlice, inColIndex));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray getSlice2DRow(NdArray<dtype>& self, int32 inRowIndex, const Slice& inColSlice)
    {
        return numCToBoost(self.at(inRowIndex, inColSlice));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray max(NdArray<dtype>& self, Axis::Type inAxis = Axis::NONE)
    {
        return numCToBoost(self.max(inAxis));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray min(NdArray<dtype>& self, Axis::Type inAxis = Axis::NONE)
    {
        return numCToBoost(self.min(inAxis));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray mean(NdArray<dtype>& self, Axis::Type inAxis = Axis::NONE)
    {
        return numCToBoost(self.mean(inAxis));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray median(NdArray<dtype>& self, Axis::Type inAxis = Axis::NONE)
    {
        return numCToBoost(self.median(inAxis));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray newbyteorder(NdArray<dtype>& self, Endian::Type inEndiness = Endian::NATIVE)
    {
        return numCToBoost(self.newbyteorder(inEndiness));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray nonzero(NdArray<dtype>& self)
    {
        return numCToBoost(self.nonzero());
    }

    //================================================================================

    template<typename dtype, typename dtypeOut>
    np::ndarray norm(NdArray<dtype>& self, Axis::Type inAxis = Axis::NONE)
    {
        return numCToBoost<dtypeOut>(self.norm<dtypeOut>(inAxis));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray ones(NdArray<dtype>& self)
    {
        self.ones();
        return numCToBoost<dtype>(self);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray partition(NdArray<dtype>& self, uint32 inKth, Axis::Type inAxis = Axis::NONE)
    {
        self.partition(inKth, inAxis);
        return numCToBoost<dtype>(self);
    }

    //================================================================================

    template<typename dtype, typename dtypeOut>
    np::ndarray prod(NdArray<dtype>& self, Axis::Type inAxis = Axis::NONE)
    {
        return numCToBoost<dtypeOut>(self.prod<dtypeOut>(inAxis));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray ptp(NdArray<dtype>& self, Axis::Type inAxis = Axis::NONE)
    {
        return numCToBoost(self.ptp(inAxis));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray putFlat(NdArray<dtype>& self, int32 inIndex, dtype inValue)
    {
        self.put(inIndex, inValue);
        return numCToBoost(self);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray putRowCol(NdArray<dtype>& self, int32 inRow, int32 inCol, dtype inValue)
    {
        self.put(inRow, inCol, inValue);
        return numCToBoost(self);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray putSlice1DValue(NdArray<dtype>& self, const Slice& inSlice, dtype inValue)
    {
        self.put(inSlice, inValue);
        return numCToBoost(self);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray putSlice1DValues(NdArray<dtype>& self, const Slice& inSlice, np::ndarray& inArrayValues)
    {
        NdArray<dtype> inValues = boostToNumC<dtype>(inArrayValues);
        self.put(inSlice, inValues);
        return numCToBoost(self);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray putSlice2DValue(NdArray<dtype>& self, const Slice& inSliceRow, const Slice& inSliceCol, dtype inValue)
    {
        self.put(inSliceRow, inSliceCol, inValue);
        return numCToBoost(self);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray putSlice2DValueRow(NdArray<dtype>& self, int32 inRowIndex, const Slice& inSliceCol, dtype inValue)
    {
        self.put(inRowIndex, inSliceCol, inValue);
        return numCToBoost(self);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray putSlice2DValueCol(NdArray<dtype>& self, const Slice& inSliceRow, int32 inColIndex, dtype inValue)
    {
        self.put(inSliceRow, inColIndex, inValue);
        return numCToBoost(self);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray putSlice2DValues(NdArray<dtype>& self, const Slice& inSliceRow, const Slice& inSliceCol, np::ndarray& inArrayValues)
    {
        NdArray<dtype> inValues = boostToNumC<dtype>(inArrayValues);
        self.put(inSliceRow, inSliceCol, inValues);
        return numCToBoost(self);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray putSlice2DValuesRow(NdArray<dtype>& self, int32 inRowIndex, const Slice& inSliceCol, np::ndarray& inArrayValues)
    {
        NdArray<dtype> inValues = boostToNumC<dtype>(inArrayValues);
        self.put(inRowIndex, inSliceCol, inValues);
        return numCToBoost(self);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray putSlice2DValuesCol(NdArray<dtype>& self, const Slice& inSliceRow, int32 inColIndex, np::ndarray& inArrayValues)
    {
        NdArray<dtype> inValues = boostToNumC<dtype>(inArrayValues);
        self.put(inSliceRow, inColIndex, inValues);
        return numCToBoost(self);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray repeat(NdArray<dtype>& self, const Shape& inRepeatShape)
    {
        return numCToBoost(self.repeat(inRepeatShape));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray reshape(NdArray<dtype>& self, const Shape& inShape)
    {
        self.reshape(inShape);
        return numCToBoost(self);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray reshapeList(NdArray<dtype>& self, const Shape& inShape)
    {
        self.reshape({ inShape.rows, inShape.cols });
        return numCToBoost(self);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray resizeFast(NdArray<dtype>& self, const Shape& inShape)
    {
        self.resizeFast(inShape);
        return numCToBoost(self);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray resizeFastList(NdArray<dtype>& self, const Shape& inShape)
    {
        self.resizeFast({ inShape.rows, inShape.cols });
        return numCToBoost(self);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray resizeSlow(NdArray<dtype>& self, const Shape& inShape)
    {
        self.resizeSlow(inShape);
        return numCToBoost(self);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray resizeSlowList(NdArray<dtype>& self, const Shape& inShape)
    {
        self.resizeSlow({ inShape.rows, inShape.cols });
        return numCToBoost(self);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray round(NdArray<dtype>& self, uint8 inNumDecimals)
    {
        return numCToBoost(self.round(inNumDecimals));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray sort(NdArray<dtype>& self, Axis::Type inAxis = Axis::NONE)
    {
        self.sort(inAxis);
        return numCToBoost(self);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray std(NdArray<dtype>& self, Axis::Type inAxis = Axis::NONE)
    {
        return numCToBoost(self.std(inAxis));
    }

    //================================================================================

    template<typename dtype, typename dtypeOut>
    np::ndarray sum(NdArray<dtype>& self, Axis::Type inAxis = Axis::NONE)
    {
        return numCToBoost(self.sum<dtypeOut>(inAxis));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray swapaxes(NdArray<dtype>& self)
    {
        return numCToBoost(self.swapaxes());
    }

    //================================================================================

    template<typename dtype>
    np::ndarray transpose(NdArray<dtype>& self)
    {
        return numCToBoost(self.transpose());
    }

    //================================================================================

    template<typename dtype>
    np::ndarray var(NdArray<dtype>& self, Axis::Type inAxis = Axis::NONE)
    {
        return numCToBoost(self.var(inAxis));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray operatorPlusScalar(NdArray<dtype>& self, dtype inScalar)
    {
        return numCToBoost(self + inScalar);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray operatorPlusArray(NdArray<dtype>& self, NdArray<dtype>& inOtherArray)
    {
        return numCToBoost(self + inOtherArray);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray operatorMinusScalar(NdArray<dtype>& self, dtype inScalar)
    {
        return numCToBoost(self - inScalar);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray operatorMinusArray(NdArray<dtype>& self, NdArray<dtype>& inOtherArray)
    {
        return numCToBoost(self - inOtherArray);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray operatorMultiplyScalar(NdArray<dtype>& self, dtype inScalar)
    {
        return numCToBoost(self * inScalar);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray operatorMultiplyArray(NdArray<dtype>& self, NdArray<dtype>& inOtherArray)
    {
        return numCToBoost(self * inOtherArray);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray operatorDivideScalar(NdArray<dtype>& self, dtype inScalar)
    {
        return numCToBoost(self / inScalar);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray operatorDivideArray(NdArray<dtype>& self, NdArray<dtype>& inOtherArray)
    {
        return numCToBoost(self / inOtherArray);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray operatorModulusScalar(NdArray<dtype>& self, dtype inScalar)
    {
        return numCToBoost(self % inScalar);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray operatorModulusArray(NdArray<dtype>& self, NdArray<dtype>& inOtherArray)
    {
        return numCToBoost(self % inOtherArray);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray operatorBitwiseOrScalar(NdArray<dtype>& self, dtype inScalar)
    {
        return numCToBoost(self | inScalar);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray operatorBitwiseOrArray(NdArray<dtype>& self, NdArray<dtype>& inOtherArray)
    {
        return numCToBoost(self | inOtherArray);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray operatorBitwiseAndScalar(NdArray<dtype>& self, dtype inScalar)
    {
        return numCToBoost(self & inScalar);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray operatorBitwiseAndArray(NdArray<dtype>& self, NdArray<dtype>& inOtherArray)
    {
        return numCToBoost(self & inOtherArray);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray operatorBitwiseXorScalar(NdArray<dtype>& self, dtype inScalar)
    {
        return numCToBoost(self ^ inScalar);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray operatorBitwiseXorArray(NdArray<dtype>& self, NdArray<dtype>& inOtherArray)
    {
        return numCToBoost(self ^ inOtherArray);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray operatorBitwiseNot(NdArray<dtype>& self)
    {
        return numCToBoost(~self);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray operatorEqualityScalar(NdArray<dtype>& self, dtype inValue)
    {
        return numCToBoost(self == inValue);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray operatorEqualityArray(NdArray<dtype>& self, NdArray<dtype>& inOtherArray)
    {
        return numCToBoost(self == inOtherArray);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray operatorLessScalar(NdArray<dtype>& self, dtype inValue)
    {
        return numCToBoost(self < inValue);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray operatorLessArray(NdArray<dtype>& self, NdArray<dtype>& inOtherArray)
    {
        return numCToBoost(self < inOtherArray);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray operatorGreaterScalar(NdArray<dtype>& self, dtype inValue)
    {
        return numCToBoost(self > inValue);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray operatorGreaterArray(NdArray<dtype>& self, NdArray<dtype>& inOtherArray)
    {
        return numCToBoost(self > inOtherArray);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray operatorLessEqualScalar(NdArray<dtype>& self, dtype inValue)
    {
        return numCToBoost(self <= inValue);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray operatorLessEqualArray(NdArray<dtype>& self, NdArray<dtype>& inOtherArray)
    {
        return numCToBoost(self <= inOtherArray);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray operatorGreaterEqualScalar(NdArray<dtype>& self, dtype inValue)
    {
        return numCToBoost(self >= inValue);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray operatorGreaterEqualArray(NdArray<dtype>& self, NdArray<dtype>& inOtherArray)
    {
        return numCToBoost(self >= inOtherArray);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray operatorNotEqualityScalar(NdArray<dtype>& self, dtype inValue)
    {
        return numCToBoost(self != inValue);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray operatorNotEqualityArray(NdArray<dtype>& self, NdArray<dtype>& inOtherArray)
    {
        return numCToBoost(self != inOtherArray);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray operatorBitshiftLeft(NdArray<dtype>& self, uint8 inNumBits)
    {
        return numCToBoost(self << inNumBits);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray operatorBitshiftRight(NdArray<dtype>& self, uint8 inNumBits)
    {
        return numCToBoost(self >> inNumBits);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray operatorPrePlusPlus(NdArray<dtype>& self)
    {
        return numCToBoost(++self);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray operatorPostPlusPlus(NdArray<dtype>& self)
    {
        return numCToBoost(self++);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray operatorPreMinusMinus(NdArray<dtype>& self)
    {
        return numCToBoost(--self);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray operatorPostMinusMinus(NdArray<dtype>& self)
    {
        return numCToBoost(self--);
    }
}

//================================================================================

namespace MethodsInterface
{
    template<typename dtype>
    dtype absScalar(dtype inValue)
    {
        return Methods<type>::abs(inValue);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray absArray(const NdArray<dtype>& inArray)
    {
        return numCToBoost(Methods<type>::abs(inArray));
    }

    //================================================================================

    template<typename dtype, typename dtypeOut>
    np::ndarray addArrays(const NdArray<dtype>& inArray1, const NdArray<dtype>& inArray2)
    {
        return numCToBoost(Methods<type>::add<dtypeOut>(inArray1, inArray2));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray allArray(const NdArray<dtype>& inArray, Axis::Type inAxis = Axis::NONE)
    {
        return numCToBoost(Methods<type>::all(inArray, inAxis));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray anyArray(const NdArray<dtype>& inArray, Axis::Type inAxis = Axis::NONE)
    {
        return numCToBoost(Methods<type>::any(inArray, inAxis));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray argmaxArray(const NdArray<dtype>& inArray, Axis::Type inAxis = Axis::NONE)
    {
        return numCToBoost(Methods<type>::argmax(inArray, inAxis));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray argminArray(const NdArray<dtype>& inArray, Axis::Type inAxis = Axis::NONE)
    {
        return numCToBoost(Methods<type>::argmin(inArray, inAxis));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray argsortArray(const NdArray<dtype>& inArray, Axis::Type inAxis = Axis::NONE)
    {
        return numCToBoost(Methods<type>::argsort(inArray, inAxis));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray argwhere(const NdArray<dtype>& inArray)
    {
        return numCToBoost(Methods<type>::argwhere(inArray));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray amaxArray(const NdArray<dtype>& inArray, Axis::Type inAxis = Axis::NONE)
    {
        return numCToBoost(amax(inArray, inAxis));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray aminArray(const NdArray<dtype>& inArray, Axis::Type inAxis = Axis::NONE)
    {
        return numCToBoost(amin(inArray, inAxis));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray arangeArray(dtype inStart, dtype inStop, dtype inStep)
    {
        return numCToBoost(arange<dtype>(inStart, inStop, inStep));
    }

    //================================================================================

    template<typename dtype>
    dtype arccosScalar(dtype inValue)
    {
        return arccos(inValue);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray arccosArray(const NdArray<dtype>& inArray)
    {
        return numCToBoost(arccos(inArray));
    }

    //================================================================================

    template<typename dtype>
    dtype arccoshScalar(dtype inValue)
    {
        return arccosh(inValue);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray arccoshArray(const NdArray<dtype>& inArray)
    {
        return numCToBoost(arccosh(inArray));
    }

    //================================================================================

    template<typename dtype>
    dtype arcsinScalar(dtype inValue)
    {
        return arcsin(inValue);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray arcsinArray(const NdArray<dtype>& inArray)
    {
        return numCToBoost(arcsin(inArray));
    }

    //================================================================================

    template<typename dtype>
    dtype arcsinhScalar(dtype inValue)
    {
        return arcsinh(inValue);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray arcsinhArray(const NdArray<dtype>& inArray)
    {
        return numCToBoost(arcsinh(inArray));
    }

    //================================================================================

    template<typename dtype>
    dtype arctanScalar(dtype inValue)
    {
        return arctan(inValue);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray arctanArray(const NdArray<dtype>& inArray)
    {
        return numCToBoost(arctan(inArray));
    }

    //================================================================================

    template<typename dtype>
    dtype arctan2Scalar(dtype inY, dtype inX)
    {
        return arctan2(inY, inX);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray arctan2Array(const NdArray<dtype>& inY, const NdArray<dtype>& inX)
    {
        return numCToBoost(arctan2(inY, inX));
    }

    //================================================================================

    template<typename dtype>
    dtype arctanhScalar(dtype inValue)
    {
        return arctanh(inValue);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray arctanhArray(const NdArray<dtype>& inArray)
    {
        return numCToBoost(arctanh(inArray));
    }

    //================================================================================

    template<typename dtype>
    dtype aroundScalar(dtype inValue, uint8 inNumDecimals)
    {
        return around(inValue, inNumDecimals);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray aroundArray(const NdArray<dtype>& inArray, uint8 inNumDecimals)
    {
        return numCToBoost(around(inArray, inNumDecimals));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray asarrayVector(const std::vector<double>& inVec)
    {
        return numCToBoost(asarray(inVec));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray asarrayList(dtype inValue1, dtype inValue2)
    {
        return numCToBoost(asarray<dtype>({ inValue1, inValue2 }));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray average(const NdArray<dtype>& inArray, Axis::Type inAxis = Axis::NONE)
    {
        return numCToBoost(inArray.mean(inAxis));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray averageWeighted(const NdArray<dtype>& inArray, const NdArray<dtype>& inWeights, Axis::Type inAxis = Axis::NONE)
    {
        return numCToBoost(Methods<type>::average(inArray, inWeights, inAxis));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray bincount(const NdArray<dtype>& inArray, uint16 inMinLength = 0)
    {
        return numCToBoost(Methods<type>::bincount(inArray, inMinLength));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray bincountWeighted(const NdArray<dtype>& inArray, const NdArray<dtype>& inWeights, uint16 inMinLength = 0)
    {
        return numCToBoost(Methods<type>::bincount(inArray, inWeights, inMinLength));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray bitwise_and(const NdArray<dtype>& inArray1, const NdArray<dtype>& inArray2)
    {
        return numCToBoost(Methods<type>::bitwise_and(inArray1, inArray2));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray bitwise_not(const NdArray<dtype>& inArray)
    {
        return numCToBoost(Methods<type>::bitwise_not(inArray));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray bitwise_or(const NdArray<dtype>& inArray1, const NdArray<dtype>& inArray2)
    {
        return numCToBoost(Methods<type>::bitwise_or(inArray1, inArray2));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray bitwise_xor(const NdArray<dtype>& inArray1, const NdArray<dtype>& inArray2)
    {
        return numCToBoost(Methods<type>::bitwise_xor(inArray1, inArray2));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray byteswap(const NdArray<dtype>& inArray)
    {
        return numCToBoost(Methods<type>::byteswap(inArray));
    }

    //================================================================================

    template<typename dtype>
    dtype cbrtScalar(dtype inValue)
    {
        return cbrt(inValue);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray cbrtArray(const NdArray<dtype>& inArray)
    {
        return numCToBoost(cbrt(inArray));
    }

    //================================================================================

    template<typename dtype>
    dtype ceilScalar(dtype inValue)
    {
        return ceil(inValue);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray ceilArray(const NdArray<dtype>& inArray)
    {
        return numCToBoost(ceil(inArray));
    }

    //================================================================================

    template<typename dtype>
    dtype clipScalar(dtype inValue, dtype inMinValue, dtype inMaxValue)
    {
        return clip(inValue, inMinValue, inMaxValue);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray clipArray(const NdArray<dtype>& inArray, dtype inMinValue, dtype inMaxValue)
    {
        return numCToBoost(clip(inArray, inMinValue, inMaxValue));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray column_stack(const NdArray<dtype>& inArray1, const NdArray<dtype>& inArray2,
        const NdArray<dtype>& inArray3, const NdArray<dtype>& inArray4)
    {
        return numCToBoost(Methods<type>::column_stack({ inArray1, inArray2, inArray3, inArray4 }));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray concatenate(const NdArray<dtype>& inArray1, const NdArray<dtype>& inArray2,
        const NdArray<dtype>& inArray3, const NdArray<dtype>& inArray4, Axis::Type inAxis)
    {
        return numCToBoost(Methods<type>::concatenate({ inArray1, inArray2, inArray3, inArray4 }, inAxis));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray copy(const NdArray<dtype>& inArray)
    {
        return numCToBoost(Methods<type>::copy(inArray));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray copySign(const NdArray<dtype>& inArray1, const NdArray<dtype>& inArray2)
    {
        return numCToBoost(Methods<type>::copySign(inArray1, inArray2));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray copyto(NdArray<dtype>& inArrayDest, const NdArray<dtype>& inArraySrc)
    {
        Methods<type>::copyto(inArrayDest, inArraySrc);
        return numCToBoost(inArrayDest);
    }

    //================================================================================

    template<typename dtype>
    dtype cosScalar(dtype inValue)
    {
        return Methods<type>::cos(inValue);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray cosArray(const NdArray<dtype>& inArray)
    {
        return numCToBoost(Methods<type>::cos(inArray));
    }

    //================================================================================

    template<typename dtype>
    dtype coshScalar(dtype inValue)
    {
        return Methods<type>::cosh(inValue);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray coshArray(const NdArray<dtype>& inArray)
    {
        return numCToBoost(Methods<type>::cosh(inArray));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray count_nonzero(const NdArray<dtype>& inArray, Axis::Type inAxis = Axis::ROW)
    {
        return numCToBoost(Methods<type>::count_nonzero(inArray, inAxis));
    }

    //================================================================================

    template<typename dtype, typename dtypeOut>
    np::ndarray cubeArray(const NdArray<dtype>& inArray)
    {
        return numCToBoost(Methods<type>::cube<dtype, dtypeOut>(inArray));
    }

    //================================================================================

    template<typename dtype, typename dtypeOut>
    np::ndarray cumprodArray(const NdArray<dtype>& inArray, Axis::Type inAxis = Axis::NONE)
    {
        return numCToBoost(cumprod<dtype, dtypeOut>(inArray, inAxis));
    }

    //================================================================================

    template<typename dtype, typename dtypeOut>
    np::ndarray cumsumArray(const NdArray<dtype>& inArray, Axis::Type inAxis = Axis::NONE)
    {
        return numCToBoost(cumsum<dtype, dtypeOut>(inArray, inAxis));
    }

    //================================================================================

    template<typename dtype>
    dtype deg2radScalar(dtype inValue)
    {
        return Methods<type>::deg2rad(inValue);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray deg2radArray(const NdArray<dtype>& inArray)
    {
        return numCToBoost(Methods<type>::deg2rad(inArray));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray deleteIndicesScalar(const NdArray<dtype>& inArray, uint32 inIndex, Axis::Type inAxis)
    {
        return numCToBoost(Methods<type>::deleteIndices(inArray, inIndex, inAxis));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray deleteIndicesSlice(const NdArray<dtype>& inArray, const Slice& inIndices, Axis::Type inAxis)
    {
        return numCToBoost(Methods<type>::deleteIndices(inArray, inIndices, inAxis));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray diagflat(const NdArray<dtype>& inArray)
    {
        return numCToBoost(Methods<type>::diagflat(inArray));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray diagonal(const NdArray<dtype>& inArray, uint32 inOffset = 0, Axis::Type inAxis = Axis::ROW)
    {
        return numCToBoost(Methods<type>::diagonal(inArray, inOffset, inAxis));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray diff(const NdArray<dtype>& inArray, Axis::Type inAxis = Axis::ROW)
    {
        return numCToBoost(Methods<type>::diff(inArray, inAxis));
    }

    //================================================================================

    template<typename dtype, typename dtypeOut>
    np::ndarray divide(const NdArray<dtype>& inArray1, const NdArray<dtype>& inArray2)
    {
        return numCToBoost(Methods<type>::divide<dtype, dtypeOut>(inArray1, inArray2));
    }

    //================================================================================

    template<typename dtype, typename dtypeOut>
    np::ndarray dot(const NdArray<dtype>& inArray1, const NdArray<dtype>& inArray2)
    {
        return numCToBoost(Methods<type>::dot<dtype, dtypeOut>(inArray1, inArray2));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray emptyRowCol(uint32 inNumRows, uint32 inNumCols)
    {
        return numCToBoost(Methods<type>::empty<dtype>(inNumRows, inNumCols));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray emptyShape(const Shape& inShape)
    {
        return numCToBoost(Methods<type>::empty<dtype>(inShape));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray equal(const NdArray<dtype>& inArray1, const NdArray<dtype>& inArray2)
    {
        return numCToBoost(Methods<type>::equal(inArray1, inArray2));
    }

    //================================================================================

    template<typename dtype>
    dtype expScalar(dtype inValue)
    {
        return Methods<type>::exp(inValue);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray expArray(const NdArray<dtype>& inArray)
    {
        return numCToBoost(Methods<type>::exp(inArray));
    }

    //================================================================================

    template<typename dtype>
    dtype exp2Scalar(dtype inValue)
    {
        return Methods<type>::exp2(inValue);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray exp2Array(const NdArray<dtype>& inArray)
    {
        return numCToBoost(Methods<type>::exp2(inArray));
    }

    //================================================================================

    template<typename dtype>
    dtype expm1Scalar(dtype inValue)
    {
        return Methods<type>::expm1(inValue);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray expm1Array(const NdArray<dtype>& inArray)
    {
        return numCToBoost(Methods<type>::expm1(inArray));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray eye1D(uint32 inN, int32 inK)
    {
        return numCToBoost(Methods<type>::eye<dtype>(inN, inK));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray eye2D(uint32 inN, uint32 inM, int32 inK)
    {
        return numCToBoost(Methods<type>::eye<dtype>(inN, inM, inK));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray eyeShape(const Shape& inShape, int32 inK)
    {
        return numCToBoost(Methods<type>::eye<dtype>(inShape, inK));
    }

    //================================================================================

    template<typename dtype>
    dtype fixScalar(dtype inValue)
    {
        return Methods<type>::fix(inValue);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray fixArray(const NdArray<dtype>& inArray)
    {
        return numCToBoost(Methods<type>::fix(inArray));
    }

    //================================================================================

    template<typename dtype>
    dtype floorScalar(dtype inValue)
    {
        return Methods<type>::floor(inValue);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray floorArray(const NdArray<dtype>& inArray)
    {
        return numCToBoost(Methods<type>::floor(inArray));
    }

    //================================================================================

    template<typename dtype>
    dtype floor_divideScalar(dtype inValue1, dtype inValue2)
    {
        return Methods<type>::floor_divide(inValue1, inValue2);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray floor_divideArray(const NdArray<dtype>& inArray1, const NdArray<dtype>& inArray2)
    {
        return numCToBoost(Methods<type>::floor_divide(inArray1, inArray2));
    }

    //================================================================================

    template<typename dtype>
    dtype fmaxScalar(dtype inValue1, dtype inValue2)
    {
        return Methods<type>::fmax(inValue1, inValue2);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray fmaxArray(const NdArray<dtype>& inArray1, const NdArray<dtype>& inArray2)
    {
        return numCToBoost(Methods<type>::fmax(inArray1, inArray2));
    }

    //================================================================================

    template<typename dtype>
    dtype fminScalar(dtype inValue1, dtype inValue2)
    {
        return Methods<type>::fmin(inValue1, inValue2);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray fminArray(const NdArray<dtype>& inArray1, const NdArray<dtype>& inArray2)
    {
        return numCToBoost(Methods<type>::fmin(inArray1, inArray2));
    }

    template<typename dtype>
    dtype fmodScalar(dtype inValue1, dtype inValue2)
    {
        return Methods<type>::fmod(inValue1, inValue2);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray fmodArray(const NdArray<dtype>& inArray1, const NdArray<dtype>& inArray2)
    {
        return numCToBoost(Methods<type>::fmod(inArray1, inArray2));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray fullSquare(uint32 inSquareSize, dtype inValue)
    {
        return numCToBoost(Methods<type>::full(inSquareSize, inValue));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray fullRowCol(uint32 inNumRows, uint32 inNumCols, dtype inValue)
    {
        return numCToBoost(Methods<type>::full(inNumRows, inNumCols, inValue));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray fullShape(const Shape& inShape, dtype inValue)
    {
        return numCToBoost(Methods<type>::full(inShape, inValue));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray hstack(const NdArray<dtype>& inArray1, const NdArray<dtype>& inArray2,
        const NdArray<dtype>& inArray3, const NdArray<dtype>& inArray4)
    {
        return numCToBoost(Methods<type>::hstack({ inArray1, inArray2, inArray3, inArray4 }));
    }

    //================================================================================

    template<typename dtype, typename dtypeOut>
    dtype hypotScalar(dtype inValue1, dtype inValue2)
    {
        return Methods<type>::hypot<dtype, dtypeOut>(inValue1, inValue2);
    }

    //================================================================================

    template<typename dtype, typename dtypeOut>
    np::ndarray hypotArray(const NdArray<dtype>& inArray1, const NdArray<dtype>& inArray2)
    {
        return numCToBoost(Methods<type>::hypot<dtype, dtypeOut>(inArray1, inArray2));
    }

    //================================================================================

    template<typename dtype>
    bool isnanScalar(dtype inValue)
    {
        return Methods<type>::isnan(inValue);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray isnanArray(const NdArray<dtype>& inArray)
    {
        return numCToBoost(Methods<type>::isnan(inArray));
    }

    //================================================================================

    template<typename dtype>
    dtype ldexpScalar(dtype inValue1, uint8 inValue2)
    {
        return Methods<type>::ldexp(inValue1, inValue2);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray ldexpArray(const NdArray<dtype>& inArray1, const NdArray<uint8>& inArray2)
    {
        return numCToBoost(Methods<type>::ldexp(inArray1, inArray2));
    }

    //================================================================================

    template<typename dtype, typename dtypeOut>
    np::ndarray negative(const NdArray<dtypeOut> inArray)
    {
        return numCToBoost(Methods<type>::negative<dtype, dtypeOut>(inArray));
    }

    //================================================================================

    template<typename dtype>
    dtype logScalar(dtype inValue)
    {
        return Methods<type>::log(inValue);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray logArray(const NdArray<dtype>& inArray)
    {
        return numCToBoost(Methods<type>::log(inArray));
    }

    //================================================================================

    template<typename dtype>
    dtype log10Scalar(dtype inValue)
    {
        return Methods<type>::log10(inValue);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray log10Array(const NdArray<dtype>& inArray)
    {
        return numCToBoost(Methods<type>::log10(inArray));
    }

    //================================================================================

    template<typename dtype>
    dtype log1pScalar(dtype inValue)
    {
        return Methods<type>::log1p(inValue);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray log1pArray(const NdArray<dtype>& inArray)
    {
        return numCToBoost(Methods<type>::log1p(inArray));
    }

    //================================================================================

    template<typename dtype>
    dtype log2Scalar(dtype inValue)
    {
        return Methods<type>::log2(inValue);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray log2Array(const NdArray<dtype>& inArray)
    {
        return numCToBoost(Methods<type>::log2(inArray));
    }

    template<typename dtype>
    dtype newbyteorderScalar(dtype inValue, Endian::Type inEndianess)
    {
        return Methods<type>::newbyteorder(inValue, inEndianess);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray newbyteorderArray(const NdArray<dtype>& inArray, Endian::Type inEndianess)
    {
        return numCToBoost(Methods<type>::newbyteorder(inArray, inEndianess));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray onesSquare(uint32 inSquareSize)
    {
        return numCToBoost(Methods<type>::ones<dtype>(inSquareSize));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray onesRowCol(uint32 inNumRows, uint32 inNumCols)
    {
        return numCToBoost(Methods<type>::ones<dtype>(inNumRows, inNumCols));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray onesShape(const Shape& inShape)
    {
        return numCToBoost(Methods<type>::ones<dtype>(inShape));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray sqrArray(const NdArray<dtype>& inArray)
    {
        return numCToBoost(Methods<type>::sqr<dtype>(inArray));
    }

    //================================================================================

    template<typename dtype, typename dtypeOut>
    np::ndarray powerArrayScalar(const NdArray<dtype>& inArray, uint8 inExponent)
    {
        return numCToBoost(Methods<type>::power<dtype, dtypeOut>(inArray, inExponent));
    }

    //================================================================================

    template<typename dtype, typename dtypeOut>
    np::ndarray powerArrayArray(const NdArray<dtype>& inArray, const NdArray<uint8>& inExponents)
    {
        return numCToBoost(Methods<type>::power<dtype, dtypeOut>(inArray, inExponents));
    }

    //================================================================================

    template<typename dtype>
    dtype rad2degScalar(dtype inValue)
    {
        return Methods<type>::rad2deg(inValue);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray rad2degArray(const NdArray<dtype>& inArray)
    {
        return numCToBoost(Methods<type>::rad2deg(inArray));
    }

    //================================================================================

    template<typename dtype, typename dtypeOut>
    dtype remainderScalar(dtype inValue1, dtype inValue2)
    {
        return Methods<type>::remainder<dtype, dtypeOut>(inValue1, inValue2);
    }

    //================================================================================

    template<typename dtype, typename dtypeOut>
    np::ndarray remainderArray(const NdArray<dtype>& inArray1, const NdArray<dtype>& inArray2)
    {
        return numCToBoost(Methods<type>::remainder<dtype, dtypeOut>(inArray1, inArray2));
    }

    //================================================================================

    template<typename dtype>
    void reshape(NdArray<dtype>& inArray, const Shape& inNewShape)
    {
        inArray.reshape(inNewShape);
    }

    //================================================================================

    template<typename dtype>
    void reshapeList(NdArray<dtype>& inArray, const Shape& inNewShape)
    {
        inArray.reshape({ inNewShape.rows, inNewShape.cols });
    }

    //================================================================================

    template<typename dtype>
    void resizeFast(NdArray<dtype>& inArray, const Shape& inNewShape)
    {
        inArray.resizeFast(inNewShape);
    }

    //================================================================================

    template<typename dtype>
    void resizeFastList(NdArray<dtype>& inArray, const Shape& inNewShape)
    {
        inArray.resizeFast({ inNewShape.rows, inNewShape.cols });
    }

    //================================================================================

    template<typename dtype>
    void resizeSlow(NdArray<dtype>& inArray, const Shape& inNewShape)
    {
        inArray.resizeSlow(inNewShape);
    }

    //================================================================================

    template<typename dtype>
    void resizeSlowList(NdArray<dtype>& inArray, const Shape& inNewShape)
    {
        inArray.resizeSlow({ inNewShape.rows, inNewShape.cols });
    }

    //================================================================================

    template<typename dtype>
    dtype rintScalar(dtype inValue)
    {
        return Methods<type>::rint(inValue);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray rintArray(const NdArray<dtype>& inArray)
    {
        return numCToBoost(Methods<type>::rint(inArray));
    }

    //================================================================================

    template<typename dtype>
    dtype roundScalar(dtype inValue, uint8 inDecimals)
    {
        return Methods<type>::round(inValue, inDecimals);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray roundArray(const NdArray<dtype>& inArray, uint8 inDecimals)
    {
        return numCToBoost(Methods<type>::round(inArray, inDecimals));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray row_stack(const NdArray<dtype>& inArray1, const NdArray<dtype>& inArray2,
        const NdArray<dtype>& inArray3, const NdArray<dtype>& inArray4)
    {
        return numCToBoost(Methods<type>::row_stack({ inArray1, inArray2, inArray3, inArray4 }));
    }

    //================================================================================

    template<typename dtype>
    int8 signScalar(dtype inValue)
    {
        return Methods<type>::sign(inValue);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray signArray(const NdArray<dtype>& inArray)
    {
        return numCToBoost(Methods<type>::sign(inArray));
    }

    //================================================================================

    template<typename dtype>
    bool signbitScalar(dtype inValue)
    {
        return Methods<type>::signbit(inValue);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray signbitArray(const NdArray<dtype>& inArray)
    {
        return numCToBoost(Methods<type>::signbit(inArray));
    }

    //================================================================================

    template<typename dtype>
    double sinScalar(dtype inValue)
    {
        return Methods<type>::sin(inValue);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray sinArray(const NdArray<dtype>& inArray)
    {
        return numCToBoost(Methods<type>::sin(inArray));
    }

    //================================================================================

    template<typename dtype>
    double sincScalar(dtype inValue)
    {
        return Methods<type>::sinc(inValue);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray sincArray(const NdArray<dtype>& inArray)
    {
        return numCToBoost(Methods<type>::sinc(inArray));
    }

    //================================================================================

    template<typename dtype>
    double sinhScalar(dtype inValue)
    {
        return Methods<type>::sinh(inValue);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray sinhArray(const NdArray<dtype>& inArray)
    {
        return numCToBoost(Methods<type>::sinh(inArray));
    }

    //================================================================================

    template<typename dtype>
    double sqrtScalar(dtype inValue)
    {
        return Methods<type>::sqrt(inValue);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray sqrtArray(const NdArray<dtype>& inArray)
    {
        return numCToBoost(Methods<type>::sqrt(inArray));
    }

    //================================================================================

    template<typename dtype>
    double squareScalar(dtype inValue)
    {
        return Methods<type>::square(inValue);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray squareArray(const NdArray<dtype>& inArray)
    {
        return numCToBoost(Methods<type>::square(inArray));
    }

    //================================================================================

    template<typename dtype>
    double tanScalar(dtype inValue)
    {
        return Methods<type>::tan(inValue);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray tanArray(const NdArray<dtype>& inArray)
    {
        return numCToBoost(Methods<type>::tan(inArray));
    }

    //================================================================================

    template<typename dtype>
    double tanhScalar(dtype inValue)
    {
        return Methods<type>::tanh(inValue);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray tanhArray(const NdArray<dtype>& inArray)
    {
        return numCToBoost(Methods<type>::tanh(inArray));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray tileRectangle(const NdArray<dtype>& inArray, uint32 inNumRows, uint32 inNumCols)
    {
        return numCToBoost(Methods<type>::tile(inArray, inNumRows, inNumCols));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray tileShape(const NdArray<dtype>& inArray, const Shape& inRepShape)
    {
        return numCToBoost(Methods<type>::tile(inArray, inRepShape));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray tileList(const NdArray<dtype>& inArray, uint32 inNumRows, uint32 inNumCols)
    {
        return numCToBoost(Methods<type>::tile(inArray, { inNumRows, inNumCols }));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray triSquare(uint32 inSquareSize, int32 inOffset)
    {
        return numCToBoost(Methods<type>::tri<dtype>(inSquareSize, inOffset));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray triRect(uint32 inNumRows, uint32 inNumCols, int32 inOffset)
    {
        return numCToBoost(Methods<type>::tri<dtype>(inNumRows, inNumCols, inOffset));
    }

    //================================================================================

    template<typename dtype>
    dtype unwrapScalar(dtype inValue)
    {
        return Methods<type>::unwrap(inValue);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray unwrapArray(const NdArray<dtype>& inArray)
    {
        return numCToBoost(Methods<type>::unwrap(inArray));
    }

    //================================================================================

    template<typename dtype>
    double truncScalar(dtype inValue)
    {
        return Methods<type>::trunc(inValue);
    }

    //================================================================================

    template<typename dtype>
    np::ndarray truncArray(const NdArray<dtype>& inArray)
    {
        return numCToBoost(Methods<type>::trunc(inArray));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray vstack(const NdArray<dtype>& inArray1, const NdArray<dtype>& inArray2,
        const NdArray<dtype>& inArray3, const NdArray<dtype>& inArray4)
    {
        return numCToBoost(Methods<type>::vstack({ inArray1, inArray2, inArray3, inArray4 }));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray zerosSquare(uint32 inSquareSize)
    {
        return numCToBoost(Methods<type>::zeros<dtype>(inSquareSize));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray zerosRowCol(uint32 inNumRows, uint32 inNumCols)
    {
        return numCToBoost(Methods<type>::zeros<dtype>(inNumRows, inNumCols));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray zerosShape(const Shape& inShape)
    {
        return numCToBoost(Methods<type>::zeros<dtype>(inShape));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray zerosList(uint32 inNumRows, uint32 inNumCols)
    {
        return numCToBoost(Methods<type>::zeros<dtype>({ inNumRows, inNumCols }));
    }
}

namespace RandomInterface
{
    template<typename dtype>
    np::ndarray permutationScalar(dtype inValue)
    {
        return numCToBoost(Random<dtype>::permutation(inValue));
    }

    //================================================================================

    template<typename dtype>
    np::ndarray permutationArray(const NdArray<dtype>& inArray)
    {
        return numCToBoost(Random<dtype>::permutation(inArray));
    }
}

namespace LinalgInterface
{
    template<typename dtype>
    np::ndarray hatArray(const NdArray<dtype>& inArray)
    {
        return numCToBoost(Linalg<dtype>::hat(inArray));
    }

    template<typename dtype, typename dtypeOut>
    np::ndarray multi_dot(const NdArray<dtype>& inArray1, const NdArray<dtype>& inArray2, const NdArray<dtype>& inArray3, const NdArray<dtype>& inArray4)
    {
        return numCToBoost(Linalg<dtype>::multi_dot<dtypeOut>({ inArray1 ,inArray2, inArray3, inArray4 }));
    }
}

namespace RotationsInterface
{
    np::ndarray angularVelocity(const Rotations::Quaternion& inQuat1, const Rotations::Quaternion& inQuat2, double inTime)
    {
        return numCToBoost(inQuat1.angularVelocity(inQuat2, inTime));
    }

    np::ndarray nlerp(const Rotations::Quaternion& inQuat1, const Rotations::Quaternion& inQuat2, double inPercent)
    {
        return numCToBoost(inQuat1.nlerp(inQuat2, inPercent).toNdArray());
    }

    np::ndarray slerp(const Rotations::Quaternion& inQuat1, const Rotations::Quaternion& inQuat2, double inPercent)
    {
        return numCToBoost(inQuat1.slerp(inQuat2, inPercent).toNdArray());
    }

    np::ndarray toDCM(const Rotations::Quaternion& inQuat)
    {
        return numCToBoost(inQuat.toDCM());
    }

    np::ndarray multiplyScalar(const Rotations::Quaternion& inQuat, double inScalar)
    {
        Rotations::Quaternion returnQuat = inQuat * inScalar;
        return numCToBoost(returnQuat.toNdArray());
    }

    template<typename dtype>
    np::ndarray multiplyArray(const Rotations::Quaternion& inQuat, const NdArray<dtype>& inArray)
    {
        NdArray<double> returnArray = inQuat * inArray;
        return numCToBoost(returnArray);
    }

    np::ndarray multiplyQuaternion(const Rotations::Quaternion& inQuat1, const Rotations::Quaternion& inQuat2)
    {
        Rotations::Quaternion returnQuat = inQuat1 * inQuat2;
        return numCToBoost(returnQuat.toNdArray());
    }

    template<typename dtype>
    np::ndarray hatArray(const NdArray<dtype>& inArray)
    {
        return numCToBoost(Rotations::hat(inArray));
    }
}

namespace RaInterface
{
    template<typename dtype>
    void print(const Coordinates::RA<dtype>& inRa)
    {
        std::cout << inRa;
    }
}

namespace DecInterface
{
    template<typename dtype>
    void print(const Coordinates::Dec<dtype>& self)
    {
        std::cout << self;
    }
}

namespace CoordinateInterface
{
    template<typename dtype>
    void print(const Coordinates::Coordinate<dtype>& self)
    {
        std::cout << self;
    }

    template<typename dtype>
    dtype degreeSeperationCoordinate(const Coordinates::Coordinate<dtype>& self, const Coordinates::Coordinate<dtype>& inOtherCoordinate)
    {
        return self.degreeSeperation(inOtherCoordinate);
    }

    template<typename dtype>
    dtype degreeSeperationVector(const Coordinates::Coordinate<dtype>& self, const NdArray<dtype>& inVec)
    {
        return self.degreeSeperation(inVec);
    }

    template<typename dtype>
    dtype radianSeperationCoordinate(const Coordinates::Coordinate<dtype>& self, const Coordinates::Coordinate<dtype>& inOtherCoordinate)
    {
        return self.radianSeperation(inOtherCoordinate);
    }

    template<typename dtype>
    dtype radianSeperationVector(const Coordinates::Coordinate<dtype>& self, const NdArray<dtype>& inVec)
    {
        return self.radianSeperation(inVec);
    }
}

namespace DataCubeInterface
{
    template<typename dtype>
    NdArray<dtype>& at(DataCube<dtype>& self, uint32 inIndex)
    {
        return self.at(inIndex);
    }

    template<typename dtype>
    NdArray<dtype>& getItem(DataCube<dtype>& self, uint32 inIndex)
    {
        return self[inIndex];
    }
}

//================================================================================

BOOST_PYTHON_MODULE(NumC)
{
    Py_Initialize();
    np::initialize(); // needs to be called first thing in the BOOST_PYTHON_MODULE for numpy

    //http://www.boost.org/doc/libs/1_60_0/libs/python/doc/html/tutorial/tutorial/exposing.html

    bp::class_<std::vector<double> >("double_vector")
        .def(bp::vector_indexing_suite<std::vector<double> >());

    // Constants.hpp
    bp::scope().attr("c") = Constants::c;
    bp::scope().attr("e") = Constants::e;
    bp::scope().attr("pi") = Constants::pi;
    bp::scope().attr("nan") = Constants::nan;
    bp::scope().attr("VERSION") = Constants::VERSION;

    // DtypeInfo.hpp
    typedef DtypeInfo<uint32> DtypeInfoUint32;
    bp::class_<DtypeInfoUint32>
        ("DtypeIntoUint32", bp::init<>())
        .def("bits", &DtypeInfoUint32::bits).staticmethod("bits")
        .def("epsilon", &DtypeInfoUint32::epsilon).staticmethod("epsilon")
        .def("isInteger", &DtypeInfoUint32::isInteger).staticmethod("isInteger")
        .def("min", &DtypeInfoUint32::min).staticmethod("min")
        .def("max", &DtypeInfoUint32::max).staticmethod("max");

    // Shape.hpp
    bp::class_<Shape>
        ("Shape", bp::init<>())
        .def(bp::init<uint32>())
        .def(bp::init<uint32, uint32>())
        .def(bp::init<Shape>())
        .def("testListContructor", &ShapeInterface::testListContructor).staticmethod("testListContructor")
        .def_readwrite("rows", &Shape::rows)
        .def_readwrite("cols", &Shape::cols)
        .def("size", &Shape::size)
        .def("print", &Shape::print)
        .def("__str__", &Shape::str)
        .def("__eq__", &Shape::operator==)
        .def("__neq__", &Shape::operator!=);

    // Slice.hpp
    bp::class_<Slice>
        ("Slice", bp::init<>())
        .def(bp::init<int32>())
        .def(bp::init<int32, int32>())
        .def(bp::init<int32, int32, int32>())
        .def(bp::init<Slice>())
        .def_readwrite("start", &Slice::start)
        .def_readwrite("stop", &Slice::stop)
        .def_readwrite("step", &Slice::step)
        .def("numElements", &Slice::numElements)
        .def("print", &Slice::print)
        .def("__str__", &Shape::str)
        .def("__eq__", &Shape::operator==)
        .def("__neq__", &Shape::operator!=);

    // Timer.hpp
    typedef Timer<std::chrono::microseconds> MicroTimer;
    bp::class_<MicroTimer>
        ("Timer", bp::init<>())
        .def(bp::init<std::string>())
        .def("tic", &MicroTimer::tic)
        .def("toc", &MicroTimer::toc);

    // Types.hpp
    bp::enum_<Axis::Type>("Axis")
        .value("NONE", Axis::NONE)
        .value("ROW", Axis::ROW)
        .value("COL", Axis::COL);

    bp::enum_<Endian::Type>("Endian")
        .value("NATIVE", Endian::NATIVE)
        .value("BIG", Endian::BIG)
        .value("LITTLE", Endian::LITTLE);

    // NdArray.hpp
    typedef NdArray<double> NdArrayDouble;
    bp::class_<NdArrayDouble>
        ("NdArray", bp::init<>())
        .def(bp::init<uint32>())
        .def(bp::init<uint32, uint32>())
        .def(bp::init<Shape>())
        .def(bp::init<NdArrayDouble>())
        .def("test1DListContructor", &NdArrayInterface::test1DListContructor<double>).staticmethod("test1DListContructor")
        .def("test2DListContructor", &NdArrayInterface::test2DListContructor<double>).staticmethod("test2DListContructor")
        .def("getNumpyArray", &NdArrayInterface::getNumpyArray<double>)
        .def("setArray", &NdArrayInterface::setArray<double>)
        .def("all", &NdArrayInterface::all<double>)
        .def("any", &NdArrayInterface::any<double>)
        .def("argmax", &NdArrayInterface::argmax<double>)
        .def("argmin", &NdArrayInterface::argmin<double>)
        .def("argsort", &NdArrayInterface::argsort<double>)
        .def("clip", &NdArrayInterface::clip<double>)
        .def("copy", &NdArrayInterface::copy<double>)
        .def("contains", &NdArrayInterface::contains<double>)
        .def("cumprod", &NdArrayInterface::cumprod<double, double>)
        //.def("cumprod", &NdArrayInterface::cumprod<double, float>)
        .def("cumsum", &NdArrayInterface::cumsum<double, double>)
        //.def("cumsum", &NdArrayInterface::cumsum<double, float>)
        .def("diagonal", &NdArrayInterface::diagonal<double>)
        .def("dot", &NdArrayInterface::dot<double, double>)
        //.def("dot", &NdArrayInterface::dot<double, float>)
        .def("dump", &NdArrayDouble::dump)
        .def("fill", &NdArrayInterface::fill<double>)
        .def("flatten", &NdArrayInterface::flatten<double>)
        .def("get", &NdArrayInterface::getValueFlat<double>)
        .def("get", &NdArrayInterface::getValueRowCol<double>)
        .def("get", &NdArrayInterface::getSlice1D<double>)
        .def("get", &NdArrayInterface::getSlice2D<double>)
        .def("get", &NdArrayInterface::getSlice2DRow<double>)
        .def("get", &NdArrayInterface::getSlice2DCol<double>)
        .def("item", &NdArrayDouble::item)
        .def("max", &NdArrayInterface::max<double>)
        .def("min", &NdArrayInterface::min<double>)
        .def("mean", &NdArrayInterface::mean<double>)
        .def("median", &NdArrayInterface::median<double>)
        .def("nbytes", &NdArrayDouble::nbytes)
        .def("nonzero", &NdArrayInterface::nonzero<double>)
        .def("norm", &NdArrayInterface::norm<double, double>)
        //.def("norm", &NdArrayInterface::norm<double, float>)
        .def("ones", &NdArrayInterface::ones<double>)
        .def("partition", &NdArrayInterface::partition<double>)
        .def("print", &NdArrayDouble::print)
        .def("prod", &NdArrayInterface::prod<double, double>)
        //.def("prod", &NdArrayInterface::prod<double, float>)
        .def("ptp", &NdArrayInterface::ptp<double>)
        .def("put", &NdArrayInterface::putFlat<double>)
        .def("put", &NdArrayInterface::putRowCol<double>)
        .def("put", &NdArrayInterface::putSlice1DValue<double>)
        .def("put", &NdArrayInterface::putSlice1DValues<double>)
        .def("put", &NdArrayInterface::putSlice2DValue<double>)
        .def("put", &NdArrayInterface::putSlice2DValueRow<double>)
        .def("put", &NdArrayInterface::putSlice2DValueCol<double>)
        .def("put", &NdArrayInterface::putSlice2DValues<double>)
        .def("put", &NdArrayInterface::putSlice2DValuesRow<double>)
        .def("put", &NdArrayInterface::putSlice2DValuesCol<double>)
        .def("repeat", &NdArrayInterface::repeat<double>)
        .def("reshape", &NdArrayInterface::reshape<double>)
        .def("reshapeList", &NdArrayInterface::reshapeList<double>)
        .def("resizeFast", &NdArrayInterface::resizeFast<double>)
        .def("resizeFastList", &NdArrayInterface::resizeFastList<double>)
        .def("resizeSlow", &NdArrayInterface::resizeSlow<double>)
        .def("resizeSlowList", &NdArrayInterface::resizeSlowList<double>)
        .def("round", &NdArrayInterface::round<double>)
        .def("shape", &NdArrayDouble::shape)
        .def("size", &NdArrayDouble::size)
        .def("sort", &NdArrayInterface::sort<double>)
        .def("std", &NdArrayInterface::std<double>)
        .def("sum", &NdArrayInterface::sum<double, double>)
        //.def("sum", &NdArrayInterface::sum<double, float>)
        .def("swapaxes", &NdArrayInterface::swapaxes<double>)
        .def("tofile", &NdArrayDouble::tofile)
        .def("toStlVector", &NdArrayDouble::toStlVector)
        .def("trace", &NdArrayDouble::trace<double>)
        .def("transpose", &NdArrayInterface::transpose<double>)
        .def("var", &NdArrayInterface::var<double>)
        .def("zeros", &NdArrayDouble::zeros)
        .def("operatorPlusScalar", &NdArrayInterface::operatorPlusScalar<double>)
        .def("operatorPlusArray", &NdArrayInterface::operatorPlusArray<double>)
        .def("operatorMinusScalar", &NdArrayInterface::operatorMinusScalar<double>)
        .def("operatorMinusArray", &NdArrayInterface::operatorMinusArray<double>)
        .def("operatorMultiplyScalar", &NdArrayInterface::operatorMultiplyScalar<double>)
        .def("operatorMultiplyArray", &NdArrayInterface::operatorMultiplyArray<double>)
        .def("operatorDivideScalar", &NdArrayInterface::operatorDivideScalar<double>)
        .def("operatorDivideArray", &NdArrayInterface::operatorDivideArray<double>)
        .def("operatorEquality", &NdArrayInterface::operatorEqualityScalar<double>)
        .def("operatorEquality", &NdArrayInterface::operatorEqualityArray<double>)
        .def("operatorLess", &NdArrayInterface::operatorLessScalar<double>)
        .def("operatorLess", &NdArrayInterface::operatorLessArray<double>)
        .def("operatorGreater", &NdArrayInterface::operatorGreaterScalar<double>)
        .def("operatorGreater", &NdArrayInterface::operatorGreaterArray<double>)
        .def("operatorLessEqual", &NdArrayInterface::operatorLessEqualScalar<double>)
        .def("operatorLessEqual", &NdArrayInterface::operatorLessEqualArray<double>)
        .def("operatorGreaterEqual", &NdArrayInterface::operatorGreaterEqualScalar<double>)
        .def("operatorGreaterEqual", &NdArrayInterface::operatorGreaterEqualArray<double>)
        .def("operatorNotEquality", &NdArrayInterface::operatorNotEqualityScalar<double>)
        .def("operatorNotEquality", &NdArrayInterface::operatorNotEqualityArray<double>)
        .def("operatorPrePlusPlus", &NdArrayInterface::operatorPrePlusPlus<double>)
        .def("operatorPostPlusPlus", &NdArrayInterface::operatorPostPlusPlus<double>)
        .def("operatorPreMinusMinus", &NdArrayInterface::operatorPreMinusMinus<double>)
        .def("operatorPostMinusMinus", &NdArrayInterface::operatorPostMinusMinus<double>);

    typedef NdArray<uint32> NdArrayInt;
    bp::class_<NdArrayInt>
        ("NdArrayInt", bp::init<>())
        .def(bp::init<uint32>())
        .def(bp::init<uint32, uint32>())
        .def(bp::init<Shape>())
        .def("item", &NdArrayInt::item)
        .def("shape", &NdArrayInt::shape)
        .def("size", &NdArrayInt::size)
        .def("getNumpyArray", &NdArrayInterface::getNumpyArray<uint32>)
        .def("endianess", &NdArrayInt::endianess)
        .def("setArray", &NdArrayInterface::setArray<uint32>)
        .def("byteswap", &NdArrayInt::byteswap)
        .def("newbyteorder", &NdArrayInterface::newbyteorder<uint32>)
        .def("operatorModulusScalar", &NdArrayInterface::operatorModulusScalar<uint32>)
        .def("operatorModulusArray", &NdArrayInterface::operatorModulusArray<uint32>)
        .def("operatorBitwiseOrScalar", &NdArrayInterface::operatorBitwiseOrScalar<uint32>)
        .def("operatorBitwiseOrArray", &NdArrayInterface::operatorBitwiseOrArray<uint32>)
        .def("operatorBitwiseAndScalar", &NdArrayInterface::operatorBitwiseAndScalar<uint32>)
        .def("operatorBitwiseAndArray", &NdArrayInterface::operatorBitwiseAndArray<uint32>)
        .def("operatorBitwiseXorScalar", &NdArrayInterface::operatorBitwiseXorScalar<uint32>)
        .def("operatorBitwiseXorArray", &NdArrayInterface::operatorBitwiseXorArray<uint32>)
        .def("operatorBitwiseNot", &NdArrayInterface::operatorBitwiseNot<uint32>)
        .def("operatorBitshiftLeft", &NdArrayInterface::operatorBitshiftLeft<uint32>)
        .def("operatorBitshiftRight", &NdArrayInterface::operatorBitshiftRight<uint32>);

    typedef NdArray<int32> NdArrayInt32;
    bp::class_<NdArrayInt32>
        ("NdArrayInt32", bp::init<>())
        .def(bp::init<uint32>())
        .def(bp::init<uint32, uint32>())
        .def(bp::init<Shape>())
        .def("item", &NdArrayInt32::item)
        .def("shape", &NdArrayInt32::shape)
        .def("size", &NdArrayInt32::size)
        .def("getNumpyArray", &NdArrayInterface::getNumpyArray<int32>)
        .def("endianess", &NdArrayInt32::endianess)
        .def("setArray", &NdArrayInterface::setArray<int32>);

    typedef NdArray<uint64> NdArrayInt64;
    bp::class_<NdArrayInt64>
        ("NdArrayInt64", bp::init<>())
        .def(bp::init<uint32>())
        .def(bp::init<uint32, uint32>())
        .def(bp::init<Shape>())
        .def("item", &NdArrayInt64::item)
        .def("shape", &NdArrayInt64::shape)
        .def("size", &NdArrayInt64::size)
        .def("getNumpyArray", &NdArrayInterface::getNumpyArray<uint64>)
        .def("endianess", &NdArrayInt64::endianess)
        .def("setArray", &NdArrayInterface::setArray<uint64>);

    typedef NdArray<uint8> NdArrayInt8;
    bp::class_<NdArrayInt8>
        ("NdArrayInt8", bp::init<>())
        .def(bp::init<uint32>())
        .def(bp::init<uint32, uint32>())
        .def(bp::init<Shape>())
        .def("item", &NdArrayInt8::item)
        .def("shape", &NdArrayInt8::shape)
        .def("size", &NdArrayInt8::size)
        .def("getNumpyArray", &NdArrayInterface::getNumpyArray<uint8>)
        .def("endianess", &NdArrayInt8::endianess)
        .def("setArray", NdArrayInterface::setArray<uint8>);

    typedef NdArray<bool> NdArrayBool;
    bp::class_<NdArrayBool>
        ("NdArrayBool", bp::init<>())
        .def(bp::init<uint32>())
        .def(bp::init<uint32, uint32>())
        .def(bp::init<Shape>())
        .def("item", &NdArrayBool::item)
        .def("shape", &NdArrayBool::shape)
        .def("size", &NdArrayBool::size)
        .def("getNumpyArray", &NdArrayInterface::getNumpyArray<bool>)
        .def("endianess", &NdArrayBool::endianess)
        .def("setArray", NdArrayInterface::setArray<bool>);

    typedef NdArray<float> NdArrayFloat;
    bp::class_<NdArrayFloat>
        ("NdArrayFloat", bp::init<>())
        .def(bp::init<uint32>())
        .def(bp::init<uint32, uint32>())
        .def(bp::init<Shape>())
        .def("item", &NdArrayFloat::item)
        .def("shape", &NdArrayFloat::shape)
        .def("size", &NdArrayFloat::size)
        .def("getNumpyArray", &NdArrayInterface::getNumpyArray<float>)
        .def("endianess", &NdArrayFloat::endianess)
        .def("setArray", &NdArrayInterface::setArray<float>);

    // Methods.hpp
    typedef Methods<double> MethodsDouble;
    bp::class_<MethodsDouble>
        ("MethodsDouble", bp::init<>())
        .def("abs", &MethodsInterface::absScalar<double>).staticmethod("abs")
        .def("abs", &MethodsInterface::absArray<double>).staticmethod("abs")
        .def("add", &MethodsInterface::addArrays<double, double>).staticmethod("add")
        //.def("add", &MethodsInterface::addArrays<double, float>).staticmethod("add")
        .def("alen", &MethodsDouble::alen).staticmethod("alen")
        .def("all", &MethodsInterface::allArray<double>).staticmethod("all")
        .def("allclose", &MethodsDouble::allclose).staticmethod("allclose")
        .def("amin", &MethodsInterface::aminArray<double>).staticmethod("amin")
        .def("amax", &MethodsInterface::amaxArray<double>).staticmethod("amax")
        .def("any", &MethodsInterface::anyArray<double>).staticmethod("any")
        .def("append", &MethodsDouble::append).staticmethod("append")
        .def("arange", &MethodsInterface::arangeArray<double>).staticmethod("arange")
        .def("argmax", &MethodsInterface::argmaxArray<double>).staticmethod("argmax")
        .def("argmin", &MethodsInterface::argminArray<double>).staticmethod("argmin")
        .def("argsort", &MethodsInterface::argsortArray<double>).staticmethod("argsort")
        .def("argwhere", &MethodsInterface::argwhere<double>).staticmethod("argwhere")
        .def("arccos", &MethodsInterface::arccosScalar<double>).staticmethod("arccos")
        .def("arccos", &MethodsInterface::arccosArray<double>).staticmethod("arccos")
        .def("arccosh", &MethodsInterface::arccoshScalar<double>).staticmethod("arccosh")
        .def("arccosh", &MethodsInterface::arccoshArray<double>).staticmethod("arccosh")
        .def("arcsin", &MethodsInterface::arcsinScalar<double>).staticmethod("arcsin")
        .def("arcsin", &MethodsInterface::arcsinArray<double>).staticmethod("arcsin")
        .def("arcsinh", &MethodsInterface::arcsinhScalar<double>).staticmethod("arcsinh")
        .def("arcsinh", &MethodsInterface::arcsinhArray<double>).staticmethod("arcsinh")
        .def("arctan", &MethodsInterface::arctanScalar<double>).staticmethod("arctan")
        .def("arctan", &MethodsInterface::arctanArray<double>).staticmethod("arctan")
        .def("arctan2", &MethodsInterface::arctan2Scalar<double>).staticmethod("arctan2")
        .def("arctan2", &MethodsInterface::arctan2Array<double>).staticmethod("arctan2")
        .def("arctanh", &MethodsInterface::arctanhScalar<double>).staticmethod("arctanh")
        .def("arctanh", &MethodsInterface::arctanhArray<double>).staticmethod("arctanh")
        .def("around", &MethodsInterface::aroundScalar<double>).staticmethod("around")
        .def("around", &MethodsInterface::aroundArray<double>).staticmethod("around")
        .def("array_equal", &MethodsDouble::array_equal).staticmethod("array_equal")
        .def("array_equiv", &MethodsDouble::array_equiv).staticmethod("array_equiv")
        .def("asarray", &MethodsInterface::asarrayVector<double>).staticmethod("asarray")
        .def("asarray", &MethodsInterface::asarrayList<double>).staticmethod("asarray")
        .def("astype", &Methods<uint32>::astype<double>).staticmethod("astype")
        .def("average", &MethodsInterface::average<double>).staticmethod("average")
        .def("average", &MethodsInterface::averageWeighted<double>).staticmethod("average")
        .def("bincount", &MethodsInterface::bincount<uint32>).staticmethod("bincount")
        .def("bincount", &MethodsInterface::bincountWeighted<uint32>).staticmethod("bincount")
        .def("bitwise_and", &MethodsInterface::bitwise_and<uint64>).staticmethod("bitwise_and")
        .def("bitwise_not", &MethodsInterface::bitwise_not<uint64>).staticmethod("bitwise_not")
        .def("bitwise_or", &MethodsInterface::bitwise_or<uint64>).staticmethod("bitwise_or")
        .def("bitwise_xor", &MethodsInterface::bitwise_xor<uint64>).staticmethod("bitwise_xor")
        .def("byteswap", &MethodsInterface::byteswap<uint64>).staticmethod("byteswap")
        .def("cbrt", &MethodsInterface::cbrtScalar<double>).staticmethod("cbrt")
        .def("cbrt", &MethodsInterface::cbrtArray<double>).staticmethod("cbrt")
        .def("ceil", &MethodsInterface::ceilScalar<double>).staticmethod("ceil")
        .def("ceil", &MethodsInterface::ceilArray<double>).staticmethod("ceil")
        .def("clip", &MethodsInterface::clipScalar<double>).staticmethod("clip")
        .def("clip", &MethodsInterface::clipArray<double>).staticmethod("clip")
        .def("column_stack", &MethodsInterface::column_stack<double>).staticmethod("column_stack")
        .def("concatenate", &MethodsInterface::concatenate<double>).staticmethod("concatenate")
        .def("contains", &MethodsDouble::contains).staticmethod("contains")
        .def("copy", &MethodsInterface::copy<double>).staticmethod("copy")
        .def("copysign", &MethodsInterface::copySign<double>).staticmethod("copysign")
        .def("copyto", &MethodsInterface::copyto<double>).staticmethod("copyto")
        .def("cos", &MethodsInterface::cosScalar<double>).staticmethod("cos")
        .def("cos", &MethodsInterface::cosArray<double>).staticmethod("cos")
        .def("cosh", &MethodsInterface::coshScalar<double>).staticmethod("cosh")
        .def("cosh", &MethodsInterface::coshArray<double>).staticmethod("cosh")
        .def("count_nonzero", &MethodsInterface::count_nonzero<double>).staticmethod("count_nonzero")
        .def("cross", &MethodsDouble::cross<double>).staticmethod("cross")
        //.def("cross", &MethodsDouble::cross<double>).staticmethod("cross")
        .def("cube", &MethodsInterface::cubeArray<double, double>).staticmethod("cube")
        //.def("cube", &MethodsInterface::cubeArray<double, float>).staticmethod("cube")
        .def("cumprod", &MethodsInterface::cumprodArray<double, double>).staticmethod("cumprod")
        //.def("cumprod", &MethodsInterface::cumprodArray<double, float>).staticmethod("cumprod")
        .def("cumsum", &MethodsInterface::cumsumArray<double, double>).staticmethod("cumsum")
        //.def("cumsum", &MethodsInterface::cumsumArray<double, float>).staticmethod("cumsum")
        .def("deg2rad", &MethodsInterface::deg2radScalar<double>).staticmethod("deg2rad")
        .def("deg2rad", &MethodsInterface::deg2radArray<double>).staticmethod("deg2rad")
        .def("delete", &MethodsInterface::deleteIndicesScalar<double>).staticmethod("delete")
        .def("delete", &MethodsInterface::deleteIndicesSlice<double>).staticmethod("delete")
        .def("diagflat", &MethodsInterface::diagflat<double>).staticmethod("diagflat")
        .def("diagonal", &MethodsInterface::diagonal<double>).staticmethod("diagonal")
        .def("diff", &MethodsInterface::diff<double>).staticmethod("diff")
        .def("divide", &MethodsInterface::divide<double, double>).staticmethod("divide")
        //.def("divide", &MethodsInterface::divide<double, float>).staticmethod("divide")
        .def("dot", &MethodsInterface::dot<double, double>).staticmethod("dot")
        //.def("dot", &MethodsInterface::dot<double, float>).staticmethod("dot")
        .def("dump", &MethodsDouble::dump).staticmethod("dump")
        .def("empty", &MethodsInterface::emptyRowCol<double>).staticmethod("empty")
        .def("empty", &MethodsInterface::emptyShape<double>).staticmethod("empty")
        .def("empty_like", &MethodsDouble::empty_like<double>).staticmethod("empty_like")
        //.def("empty_like", &MethodsDouble::empty_like<float>).staticmethod("empty_like")
        .def("endianess", &MethodsDouble::endianess).staticmethod("endianess")
        .def("equal", &MethodsInterface::equal<double>).staticmethod("equal")
        .def("exp", &MethodsInterface::expScalar<double>).staticmethod("exp")
        .def("exp", &MethodsInterface::expArray<double>).staticmethod("exp")
        .def("exp2", &MethodsInterface::exp2Scalar<double>).staticmethod("exp2")
        .def("exp2", &MethodsInterface::exp2Array<double>).staticmethod("exp2")
        .def("expm1", &MethodsInterface::expm1Scalar<double>).staticmethod("expm1")
        .def("expm1", &MethodsInterface::expm1Array<double>).staticmethod("expm1")
        .def("eye", &MethodsInterface::eye1D<double>).staticmethod("eye")
        .def("eye", &MethodsInterface::eye2D<double>).staticmethod("eye")
        .def("eye", &MethodsInterface::eyeShape<double>).staticmethod("eye")
        .def("fix", &MethodsInterface::fixScalar<double>).staticmethod("fix")
        .def("fix", &MethodsInterface::fixArray<double>).staticmethod("fix")
        .def("flatten", &MethodsDouble::flatten).staticmethod("flatten")
        .def("flatnonzero", &MethodsDouble::flatnonzero).staticmethod("flatnonzero")
        .def("flip", &MethodsDouble::flip).staticmethod("flip")
        .def("fliplr", &MethodsDouble::fliplr).staticmethod("fliplr")
        .def("flipud", &MethodsDouble::flipud).staticmethod("flipud")
        .def("floor", &MethodsInterface::floorScalar<double>).staticmethod("floor")
        .def("floor", &MethodsInterface::floorArray<double>).staticmethod("floor")
        .def("floor_divide", &MethodsInterface::floor_divideScalar<double>).staticmethod("floor_divide")
        .def("floor_divide", &MethodsInterface::floor_divideArray<double>).staticmethod("floor_divide")
        .def("fmax", &MethodsInterface::fmaxScalar<double>).staticmethod("fmax")
        .def("fmax", &MethodsInterface::fmaxArray<double>).staticmethod("fmax")
        .def("fmin", &MethodsInterface::fminScalar<double>).staticmethod("fmin")
        .def("fmin", &MethodsInterface::fminArray<double>).staticmethod("fmin")
        .def("fmod", &MethodsInterface::fmodScalar<uint32>).staticmethod("fmod")
        .def("fmod", &MethodsInterface::fmodArray<uint32>).staticmethod("fmod")
        .def("fromfile", &MethodsDouble::fromfile).staticmethod("fromfile")
        .def("full", &MethodsInterface::fullSquare<double>).staticmethod("full")
        .def("full", &MethodsInterface::fullRowCol<double>).staticmethod("full")
        .def("full", &MethodsInterface::fullShape<double>).staticmethod("full")
        .def("full_like", &MethodsDouble::full_like<double>).staticmethod("full_like")
        //.def("full_like", &MethodsDouble::full_like<float>).staticmethod("full_like")
        .def("greater", &MethodsDouble::greater).staticmethod("greater")
        .def("greater_equal", &MethodsDouble::greater_equal).staticmethod("greater_equal")
        .def("hstack", &MethodsInterface::hstack<double>).staticmethod("hstack")
        .def("hypot", &MethodsInterface::hypotScalar<double, double>).staticmethod("hypot")
        //.def("hypot", &MethodsInterface::hypotScalar<double, float>).staticmethod("hypot")
        .def("hypot", &MethodsInterface::hypotArray<double, double>).staticmethod("hypot")
        //.def("hypot", &MethodsInterface::hypotArray<double, float>).staticmethod("hypot")
        .def("identity", &MethodsDouble::identity).staticmethod("identity")
        .def("intersect1d", &Methods<uint32>::intersect1d).staticmethod("intersect1d")
        .def("invert", &Methods<uint32>::invert).staticmethod("invert")
        .def("isclose", &MethodsDouble::isclose).staticmethod("isclose")
        .def("isnan", &MethodsInterface::isnanScalar<double>).staticmethod("isnan")
        .def("isnan", &MethodsInterface::isnanArray<double>).staticmethod("isnan")
        .def("ldexp", &MethodsInterface::ldexpScalar<double>).staticmethod("ldexp")
        .def("ldexp", &MethodsInterface::ldexpArray<double>).staticmethod("ldexp")
        .def("left_shift", &Methods<uint32>::left_shift).staticmethod("left_shift")
        .def("less", &MethodsDouble::less).staticmethod("less")
        .def("less_equal", &MethodsDouble::less_equal).staticmethod("less_equal")
        .def("linspace", &MethodsDouble::linspace).staticmethod("linspace")
        .def("load", &MethodsDouble::load).staticmethod("load")
        .def("log", &MethodsInterface::logScalar<double>).staticmethod("log")
        .def("log", &MethodsInterface::logArray<double>).staticmethod("log")
        .def("log10", &MethodsInterface::log10Scalar<double>).staticmethod("log10")
        .def("log10", &MethodsInterface::log10Array<double>).staticmethod("log10")
        .def("log1p", &MethodsInterface::log1pScalar<double>).staticmethod("log1p")
        .def("log1p", &MethodsInterface::log1pArray<double>).staticmethod("log1p")
        .def("log2", &MethodsInterface::log2Scalar<double>).staticmethod("log2")
        .def("log2", &MethodsInterface::log2Array<double>).staticmethod("log2")
        .def("logical_and", &MethodsDouble::logical_and).staticmethod("logical_and")
        .def("logical_not", &MethodsDouble::logical_not).staticmethod("logical_not")
        .def("logical_or", &MethodsDouble::logical_or).staticmethod("logical_or")
        .def("logical_xor", &MethodsDouble::logical_xor).staticmethod("logical_xor")
        .def("matmul", &MethodsDouble::matmul<double>).staticmethod("matmul")
        //.def("matmul", &MethodsDouble::matmul<double, float>).staticmethod("matmul")
        .def("max", &MethodsDouble::max).staticmethod("max")
        .def("maximum", &MethodsDouble::maximum).staticmethod("maximum")
        .def("mean", &MethodsDouble::mean).staticmethod("mean")
        .def("median", &MethodsDouble::median).staticmethod("median")
        .def("min", &MethodsDouble::min).staticmethod("min")
        .def("minimum", &MethodsDouble::minimum).staticmethod("minimum")
        .def("mod", &Methods<uint32>::mod).staticmethod("mod")
        .def("multiply", &MethodsDouble::multiply).staticmethod("multiply")
        .def("nanargmax", &MethodsDouble::nanargmax).staticmethod("nanargmax")
        .def("nanargmin", &MethodsDouble::nanargmin).staticmethod("nanargmin")
        .def("nancumprod", &MethodsDouble::nancumprod<double>).staticmethod("nancumprod")
        //.def("nancumprod", &MethodsDouble::nancumprod<float>).staticmethod("nancumprod")
        .def("nancumsum", &MethodsDouble::nancumsum<double>).staticmethod("nancumsum")
        //.def("nancumsum", &MethodsDouble::nancumsum<float>).staticmethod("nancumsum")
        .def("nanmax", &MethodsDouble::nanmax).staticmethod("nanmax")
        .def("nanmean", &MethodsDouble::nanmean).staticmethod("nanmean")
        .def("nanmedian", &MethodsDouble::nanmedian).staticmethod("nanmedian")
        .def("nanmin", &MethodsDouble::nanmin).staticmethod("nanmin")
        .def("nanpercentile", &MethodsDouble::nanpercentile<double>).staticmethod("nanpercentile")
        .def("nanprod", &MethodsDouble::nanprod<double>).staticmethod("nanprod")
        //.def("nanprod", &MethodsDouble::nanprod<float>).staticmethod("nanprod")
        .def("nanstd", &MethodsDouble::nanstd).staticmethod("nanstd")
        .def("nansum", &MethodsDouble::nansum<double>).staticmethod("nansum")
        //.def("nansum", &MethodsDouble::nansum<double, float>).staticmethod("nansum")
        .def("nanvar", &MethodsDouble::nanvar).staticmethod("nanvar")
        .def("nbytes", &MethodsDouble::nbytes).staticmethod("nbytes")
        .def("newbyteorder", &MethodsInterface::newbyteorderScalar<uint32>).staticmethod("newbyteorder")
        .def("newbyteorder", &MethodsInterface::newbyteorderArray<uint32>).staticmethod("newbyteorder")
        .def("negative", &MethodsDouble::negative<double>).staticmethod("negative")
        //.def("negative", &MethodsDouble::negative<float>).staticmethod("negative")
        .def("nonzero", &MethodsDouble::nonzero).staticmethod("nonzero")
        .def("norm", &MethodsDouble::norm<double>).staticmethod("norm")
        //.def("norm", &MethodsDouble::norm<double, float>).staticmethod("norm")
        .def("not_equal", &MethodsDouble::not_equal).staticmethod("not_equal")
        .def("ones", &MethodsInterface::onesSquare<double>).staticmethod("ones")
        .def("ones", &MethodsInterface::onesRowCol<double>).staticmethod("ones")
        .def("ones", &MethodsInterface::onesShape<double>).staticmethod("ones")
        .def("ones_like", &MethodsDouble::ones_like<double>).staticmethod("ones_like")
        //.def("ones_like", &MethodsDouble::ones_like<double, float>).staticmethod("ones_like")
        .def("pad", &MethodsDouble::pad).staticmethod("pad")
        .def("partition", &MethodsDouble::partition).staticmethod("partition")
        .def("percentile", &MethodsDouble::percentile<double>).staticmethod("percentile")
        //.def("percentile", &MethodsDouble::percentile<double, float>).staticmethod("percentile")
        .def("power", &MethodsInterface::powerArrayScalar<double, double>).staticmethod("power")
        //.def("power", &MethodsInterface::powerArrayScalar<double, float>).staticmethod("power")
        .def("power", &MethodsInterface::powerArrayArray<double, double>).staticmethod("power")
        //.def("power", &MethodsInterface::powerArrayArray<double, float>).staticmethod("power")
        .def("prod", &MethodsDouble::prod<double>).staticmethod("prod")
        //.def("prod", &MethodsDouble::prod<double, float>).staticmethod("prod")
        .def("ptp", &MethodsDouble::ptp).staticmethod("ptp")
        .def("put", &MethodsDouble::put).staticmethod("put")
        .def("rad2deg", &MethodsInterface::rad2degScalar<double>).staticmethod("rad2deg")
        .def("rad2deg", &MethodsInterface::rad2degArray<double>).staticmethod("rad2deg")
        .def("reciprocal", &MethodsDouble::reciprocal<double>).staticmethod("reciprocal")
        //.def("reciprocal", &MethodsDouble::reciprocal<double, float>).staticmethod("reciprocal")
        .def("remainder", &MethodsInterface::remainderScalar<double, double>).staticmethod("remainder")
        //.def("remainder", &MethodsInterface::remainderScalar<double, float>).staticmethod("remainder")
        .def("remainder", &MethodsInterface::remainderArray<double, double>).staticmethod("remainder")
        //.def("remainder", &MethodsInterface::remainderArray<double, float>).staticmethod("remainder")
        .def("reshape", &MethodsInterface::reshape<double>).staticmethod("reshape")
        .def("reshapeList", &MethodsInterface::reshapeList<double>).staticmethod("reshapeList")
        .def("resizeFast", &MethodsInterface::resizeFast<double>).staticmethod("resizeFast")
        .def("resizeFastList", &MethodsInterface::resizeFastList<double>).staticmethod("resizeFastList")
        .def("resizeSlow", &MethodsInterface::resizeSlow<double>).staticmethod("resizeSlow")
        .def("resizeSlowList", &MethodsInterface::resizeSlowList<double>).staticmethod("resizeSlowList")
        .def("right_shift", &Methods<uint32>::right_shift).staticmethod("right_shift")
        .def("rint", &MethodsInterface::rintScalar<double>).staticmethod("rint")
        .def("rint", &MethodsInterface::rintArray<double>).staticmethod("rint")
        .def("roll", &MethodsDouble::roll).staticmethod("roll")
        .def("rot90", &MethodsDouble::rot90).staticmethod("rot90")
        .def("round", &MethodsInterface::roundScalar<double>).staticmethod("round")
        .def("round", &MethodsInterface::roundArray<double>).staticmethod("round")
        .def("row_stack", &MethodsInterface::row_stack<double>).staticmethod("row_stack")
        .def("setdiff1d", &Methods<uint32>::setdiff1d).staticmethod("setdiff1d")
        .def("sign", &MethodsInterface::signScalar<double>).staticmethod("sign")
        .def("sign", &MethodsInterface::signArray<double>).staticmethod("sign")
        .def("signbit", &MethodsInterface::signbitScalar<double>).staticmethod("signbit")
        .def("signbit", &MethodsInterface::signbitArray<double>).staticmethod("signbit")
        .def("sin", &MethodsInterface::sinScalar<double>).staticmethod("sin")
        .def("sin", &MethodsInterface::sinArray<double>).staticmethod("sin")
        .def("sinc", &MethodsInterface::sincScalar<double>).staticmethod("sinc")
        .def("sinc", &MethodsInterface::sincArray<double>).staticmethod("sinc")
        .def("sinh", &MethodsInterface::sinhScalar<double>).staticmethod("sinh")
        .def("sinh", &MethodsInterface::sinhArray<double>).staticmethod("sinh")
        .def("size", &MethodsDouble::size).staticmethod("size")
        .def("sort", &MethodsDouble::sort).staticmethod("sort")
        .def("sqrt", &MethodsInterface::sqrtScalar<double>).staticmethod("sqrt")
        .def("sqrt", &MethodsInterface::sqrtArray<double>).staticmethod("sqrt")
        .def("square", &MethodsInterface::squareScalar<double>).staticmethod("square")
        .def("square", &MethodsInterface::squareArray<double>).staticmethod("square")
        .def("std", &MethodsDouble::std).staticmethod("std")
        .def("sum", &MethodsDouble::sum<double>).staticmethod("sum")
        //.def("sum", &MethodsDouble::sum<float>).staticmethod("sum")
        .def("swapaxes", &MethodsDouble::swapaxes).staticmethod("swapaxes")
        .def("tan", &MethodsInterface::tanScalar<double>).staticmethod("tan")
        .def("tan", &MethodsInterface::tanArray<double>).staticmethod("tan")
        .def("tanh", &MethodsInterface::tanhScalar<double>).staticmethod("tanh")
        .def("tanh", &MethodsInterface::tanhArray<double>).staticmethod("tanh")
        .def("tile", &MethodsInterface::tileRectangle<double>).staticmethod("tile")
        .def("tile", &MethodsInterface::tileShape<double>).staticmethod("tile")
        .def("tileList", &MethodsInterface::tileList<double>).staticmethod("tileList")
        .def("tofile", &MethodsDouble::tofile).staticmethod("tofile")
        .def("toStlVector", &MethodsDouble::toStlVector).staticmethod("toStlVector")
        .def("trace", &MethodsDouble::trace<double>).staticmethod("trace")
        //.def("trace", &MethodsDouble::trace<double, float>).staticmethod("trace")
        .def("transpose", &MethodsDouble::transpose).staticmethod("transpose")
        .def("tri", &MethodsInterface::triSquare<double>).staticmethod("tri")
        .def("tri", &MethodsInterface::triRect<double>).staticmethod("tri")
        //.def("tril", &MethodsDouble::tril).staticmethod("tril")
        //.def("triu", &MethodsDouble::triu).staticmethod("triu")
        .def("trim_zeros", &MethodsDouble::trim_zeros).staticmethod("trim_zeros")
        .def("trunc", &MethodsInterface::truncScalar<double>).staticmethod("trunc")
        .def("trunc", &MethodsInterface::truncArray<double>).staticmethod("trunc")
        .def("union1d", &Methods<uint32>::union1d).staticmethod("union1d")
        .def("unique", &MethodsDouble::unique).staticmethod("unique")
        .def("unwrap", &MethodsInterface::unwrapScalar<double>).staticmethod("unwrap")
        .def("unwrap", &MethodsInterface::unwrapArray<double>).staticmethod("unwrap")
        .def("var", &MethodsDouble::var).staticmethod("var")
        .def("vstack", &MethodsInterface::vstack<double>).staticmethod("vstack")
        .def("zeros", &MethodsInterface::zerosSquare<double>).staticmethod("zeros")
        .def("zeros", &MethodsInterface::zerosRowCol<double>).staticmethod("zeros")
        .def("zeros", &MethodsInterface::zerosShape<double>).staticmethod("zeros")
        .def("zerosList", &MethodsInterface::zerosList<double>).staticmethod("zerosList");

    // Utils.hpp
    typedef Utils<double> UtilsDouble;
    bp::class_<UtilsDouble>
        ("UtilsDouble", bp::init<>())
        .def("num2str", &UtilsDouble::num2str).staticmethod("num2str")
        .def("sqr", &UtilsDouble::sqr).staticmethod("sqr")
        .def("cube", &UtilsDouble::cube).staticmethod("cube")
        .def("power", &UtilsDouble::power).staticmethod("power");

    typedef Utils<float> UtilsFloat;
    bp::class_<UtilsFloat>
        ("UtilsFloat", bp::init<>())
        .def("num2str", &UtilsFloat::num2str).staticmethod("num2str")
        .def("sqr", &UtilsFloat::sqr).staticmethod("sqr")
        .def("cube", &UtilsFloat::cube).staticmethod("cube")
        .def("power", &UtilsFloat::power).staticmethod("power");

    typedef Utils<int8> UtilsInt8;
    bp::class_<UtilsInt8>
        ("UtilsInt8", bp::init<>())
        .def("num2str", &UtilsInt8::num2str).staticmethod("num2str")
        .def("sqr", &UtilsInt8::sqr).staticmethod("sqr")
        .def("cube", &UtilsInt8::cube).staticmethod("cube")
        .def("power", &UtilsInt8::power).staticmethod("power");

    typedef Utils<int16> UtilsInt16;
    bp::class_<UtilsInt16>
        ("UtilsInt16", bp::init<>())
        .def("num2str", &UtilsInt16::num2str).staticmethod("num2str")
        .def("sqr", &UtilsInt16::sqr).staticmethod("sqr")
        .def("cube", &UtilsInt16::cube).staticmethod("cube")
        .def("power", &UtilsInt16::power).staticmethod("power");

    typedef Utils<int32> UtilsInt32;
    bp::class_<UtilsInt32>
        ("UtilsInt32", bp::init<>())
        .def("num2str", &UtilsInt32::num2str).staticmethod("num2str")
        .def("sqr", &UtilsInt32::sqr).staticmethod("sqr")
        .def("cube", &UtilsInt32::cube).staticmethod("cube")
        .def("power", &UtilsInt32::power).staticmethod("power");

    typedef Utils<int64> UtilsInt64;
    bp::class_<UtilsInt64>
        ("UtilsInt32", bp::init<>())
        .def("num2str", &UtilsInt64::num2str).staticmethod("num2str")
        .def("sqr", &UtilsInt64::sqr).staticmethod("sqr")
        .def("cube", &UtilsInt64::cube).staticmethod("cube")
        .def("power", &UtilsInt64::power).staticmethod("power");

    typedef Utils<uint8> UtilsUint8;
    bp::class_<UtilsUint8>
        ("UtilsUint8", bp::init<>())
        .def("num2str", &UtilsUint8::num2str).staticmethod("num2str")
        .def("sqr", &UtilsUint8::sqr).staticmethod("sqr")
        .def("cube", &UtilsUint8::cube).staticmethod("cube")
        .def("power", &UtilsUint8::power).staticmethod("power");

    typedef Utils<uint16> UtilsUint16;
    bp::class_<UtilsUint16>
        ("UtilsInt16", bp::init<>())
        .def("num2str", &UtilsUint16::num2str).staticmethod("num2str")
        .def("sqr", &UtilsUint16::sqr).staticmethod("sqr")
        .def("cube", &UtilsUint16::cube).staticmethod("cube")
        .def("power", &UtilsUint16::power).staticmethod("power");

    typedef Utils<uint32> UtilsUint32;
    bp::class_<UtilsUint32>
        ("UtilsUint32", bp::init<>())
        .def("num2str", &UtilsUint32::num2str).staticmethod("num2str")
        .def("sqr", &UtilsUint32::sqr).staticmethod("sqr")
        .def("cube", &UtilsUint32::cube).staticmethod("cube")
        .def("power", &UtilsUint32::power).staticmethod("power");

    typedef Utils<uint64> UtilsUint64;
    bp::class_<UtilsUint64>
        ("UtilsInt32", bp::init<>())
        .def("num2str", &UtilsUint64::num2str).staticmethod("num2str")
        .def("sqr", &UtilsUint64::sqr).staticmethod("sqr")
        .def("cube", &UtilsUint64::cube).staticmethod("cube")
        .def("power", &UtilsUint64::power).staticmethod("power");

    // Random.hpp
    typedef NumC::Random<double> RandomDouble;
    bp::class_<RandomDouble>
        ("Random", bp::init<>())
        .def("bernoulli", &RandomDouble::bernoulli).staticmethod("bernoulli")
        .def("beta", &RandomDouble::beta).staticmethod("beta")
        .def("binomial", &RandomDouble::binomial).staticmethod("binomial")
        .def("chiSquare", &RandomDouble::chiSquare).staticmethod("chiSquare")
        .def("choice", &RandomDouble::choice).staticmethod("choice")
        .def("cauchy", &RandomDouble::cauchy).staticmethod("cauchy")
        .def("discrete", &RandomDouble::discrete).staticmethod("discrete")
        .def("exponential", &RandomDouble::exponential).staticmethod("exponential")
        .def("extremeValue", &RandomDouble::extremeValue).staticmethod("extremeValue")
        .def("f", &RandomDouble::f).staticmethod("f")
        .def("gamma", &RandomDouble::gamma).staticmethod("gamma")
        .def("geometric", &RandomDouble::geometric).staticmethod("geometric")
        .def("laplace", &RandomDouble::laplace).staticmethod("laplace")
        .def("lognormal", &RandomDouble::lognormal).staticmethod("lognormal")
        .def("negativeBinomial", &RandomDouble::negativeBinomial).staticmethod("negativeBinomial")
        .def("nonCentralChiSquared", &RandomDouble::nonCentralChiSquared).staticmethod("nonCentralChiSquared")
        .def("normal", &RandomDouble::normal).staticmethod("normal")
        .def("permutation", &RandomInterface::permutationScalar<double>).staticmethod("permutation")
        .def("permutation", &RandomInterface::permutationArray<double>).staticmethod("permutation")
        .def("poisson", &RandomDouble::poisson).staticmethod("poisson")
        .def("rand", &RandomDouble::rand).staticmethod("rand")
        .def("randN", &RandomDouble::randN).staticmethod("randN")
        .def("randFloat", &RandomDouble::randFloat).staticmethod("randFloat")
        .def("randInt", &RandomDouble::randInt).staticmethod("randInt")
        .def("seed", &RandomDouble::seed).staticmethod("seed")
        .def("shuffle", &RandomDouble::shuffle).staticmethod("shuffle")
        .def("studentT", &RandomDouble::studentT).staticmethod("studentT")
        .def("standardNormal", &RandomDouble::standardNormal).staticmethod("standardNormal")
        .def("triangle", &RandomDouble::triangle).staticmethod("triangle")
        .def("uniform", &RandomDouble::uniform).staticmethod("uniform")
        .def("uniformOnSphere", &RandomDouble::uniformOnSphere).staticmethod("uniformOnSphere")
        .def("weibull", &RandomDouble::weibull).staticmethod("weibull");

    // Linalg.hpp
    typedef NumC::Linalg<double> LinalgDouble;
    bp::class_<LinalgDouble>
        ("Linalg", bp::init<>())
        .def("det", &LinalgDouble::det).staticmethod("det")
        .def("hat", &LinalgInterface::hatArray<double>).staticmethod("hat")
        .def("inv", &LinalgDouble::inv).staticmethod("inv")
        .def("lstsq", &LinalgDouble::lstsq).staticmethod("lstsq")
        .def("matrix_power", &LinalgDouble::matrix_power<double>).staticmethod("matrix_power")
        //.def("matrix_power", &LinalgDouble::matrix_power<float>).staticmethod("matrix_power")
        .def("multi_dot", &LinalgInterface::multi_dot<double, double>).staticmethod("multi_dot")
        //.def("multi_dot", &LinalgInterface::multi_dot<float, float>).staticmethod("multi_dot")
        .def("svd", &LinalgDouble::svd).staticmethod("svd");

    // Rotations.hpp
    bp::class_<Rotations::Quaternion>
        ("Quaternion", bp::init<>())
        .def(bp::init<double, double, double, double>())
        .def(bp::init<NdArray<double> >())
        .def("angleAxisRotation", &Rotations::Quaternion::angleAxisRotation<double>).staticmethod("angleAxisRotation")
        .def("angularVelocity", &RotationsInterface::angularVelocity)
        .def("conjugate", &Rotations::Quaternion::conjugate)
        .def("i", &Rotations::Quaternion::i)
        .def("identity", &Rotations::Quaternion::identity).staticmethod("identity")
        .def("inverse", &Rotations::Quaternion::inverse)
        .def("j", &Rotations::Quaternion::j)
        .def("k", &Rotations::Quaternion::k)
        .def("fromDCM", &Rotations::Quaternion::fromDCM<double>).staticmethod("fromDCM")
        .def("nlerp", &RotationsInterface::nlerp)
        .def("nlerp", &RotationsInterface::nlerp)
        .def("print", &Rotations::Quaternion::print)
        .def("rotate", &Rotations::Quaternion::rotate<double>)
        .def("s", &Rotations::Quaternion::s)
        .def("slerp", &RotationsInterface::slerp)
        .def("slerp", &RotationsInterface::slerp)
        .def("toDCM", &RotationsInterface::toDCM)
        .def("toNdArray", &Rotations::Quaternion::toNdArray)
        .def("xRotation", &Rotations::Quaternion::xRotation).staticmethod("xRotation")
        .def("yRotation", &Rotations::Quaternion::yRotation).staticmethod("yRotation")
        .def("zRotation", &Rotations::Quaternion::zRotation).staticmethod("zRotation")
        .def("__eq__", &Rotations::Quaternion::operator==)
        .def("__neq__", &Rotations::Quaternion::operator!=)
        .def("__add__", &Rotations::Quaternion::operator+)
        .def("__sub__", &Rotations::Quaternion::operator-)
        .def("__mul__", &RotationsInterface::multiplyScalar)
        .def("__mul__", &RotationsInterface::multiplyQuaternion)
        .def("__mul__", &RotationsInterface::multiplyArray<double>)
        .def("__truediv__", &Rotations::Quaternion::operator/)
        .def("__str__", &Rotations::Quaternion::str);

    typedef Rotations::DCM<double> DCMDouble;
    bp::class_<DCMDouble>
        ("DCM", bp::init<>())
        .def("angleAxisRotationDCM", &DCMDouble::angleAxisRotationDCM).staticmethod("angleAxisRotationDCM")
        .def("isValidDCM", &DCMDouble::isValidDCM).staticmethod("isValidDCM")
        .def("xRotationDCM", &DCMDouble::xRotationDCM).staticmethod("xRotationDCM")
        .def("yRotationDCM", &DCMDouble::yRotationDCM).staticmethod("yRotationDCM")
        .def("zRotationDCM", &DCMDouble::zRotationDCM).staticmethod("zRotationDCM");

    // Filters
    bp::enum_<Filter::Boundary::Mode>("Mode")
        .value("REFLECT", Filter::Boundary::REFLECT)
        .value("CONSTANT", Filter::Boundary::CONSTANT)
        .value("NEAREST", Filter::Boundary::NEAREST)
        .value("MIRROR", Filter::Boundary::MIRROR)
        .value("WRAP", Filter::Boundary::WRAP);

    typedef Filters<double> FiltersDouble;

    bp::class_<FiltersDouble>
        ("Filters", bp::init<>())
        .def("complementaryMedianFilter", &FiltersDouble::complementaryMedianFilter).staticmethod("complementaryMedianFilter")
        .def("complementaryMedianFilter1d", &FiltersDouble::complementaryMedianFilter1d).staticmethod("complementaryMedianFilter1d")
        .def("convolve", &FiltersDouble::convolve).staticmethod("convolve")
        .def("convolve1d", &FiltersDouble::convolve1d).staticmethod("convolve1d")
        .def("gaussianFilter", &FiltersDouble::gaussianFilter).staticmethod("gaussianFilter")
        .def("gaussianFilter1d", &FiltersDouble::gaussianFilter1d).staticmethod("gaussianFilter1d")
        .def("maximumFilter", &FiltersDouble::maximumFilter).staticmethod("maximumFilter")
        .def("maximumFilter1d", &FiltersDouble::maximumFilter1d).staticmethod("maximumFilter1d")
        .def("medianFilter", &FiltersDouble::medianFilter).staticmethod("medianFilter")
        .def("medianFilter1d", &FiltersDouble::medianFilter1d).staticmethod("medianFilter1d")
        .def("minimumFilter", &FiltersDouble::minimumFilter).staticmethod("minimumFilter")
        .def("minumumFilter1d", &FiltersDouble::minumumFilter1d).staticmethod("minumumFilter1d")
        .def("percentileFilter", &FiltersDouble::percentileFilter).staticmethod("percentileFilter")
        .def("percentileFilter1d", &FiltersDouble::percentileFilter1d).staticmethod("percentileFilter1d")
        .def("rankFilter", &FiltersDouble::rankFilter).staticmethod("rankFilter")
        .def("rankFilter1d", &FiltersDouble::rankFilter1d).staticmethod("rankFilter1d")
        .def("uniformFilter", &FiltersDouble::uniformFilter).staticmethod("uniformFilter")
        .def("uniformFilter1d", &FiltersDouble::uniformFilter1d).staticmethod("uniformFilter1d");

    // Image Processing
    typedef ImageProcessing<double> ImageProcessingDouble;

    typedef ImageProcessingDouble::Pixel PixelDouble;
    bp::class_<PixelDouble>
        ("Pixel", bp::init<>())
        .def(bp::init<uint32, uint32, double>())
        .def(bp::init<PixelDouble>())
        .def("__eq__", &PixelDouble::operator==)
        .def("__ne__", &PixelDouble::operator!=)
        .def("__lt__", &PixelDouble::operator<)
        .def("clusterId", &PixelDouble::clusterId)
        .def("setClusterId", &PixelDouble::setClusterId)
        .def("row", &PixelDouble::row)
        .def("col", &PixelDouble::col)
        .def("intensity", &PixelDouble::intensity)
        .def("__str__", &PixelDouble::str)
        .def("print", &PixelDouble::print);

    typedef ImageProcessingDouble::Cluster ClusterDouble;
    bp::class_<ClusterDouble>
        ("Cluster", bp::init<uint32>())
        .def(bp::init<ClusterDouble>())
        .def("__eq__", &ClusterDouble::operator==)
        .def("__ne__", &ClusterDouble::operator!=)
        .def("__getitem__", &ClusterDouble::at, bp::return_internal_reference<>())
        .def("size", &ClusterDouble::size)
        .def("clusterId", &ClusterDouble::clusterId)
        .def("rowMin", &ClusterDouble::rowMin)
        .def("rowMax", &ClusterDouble::rowMax)
        .def("colMin", &ClusterDouble::colMin)
        .def("colMax", &ClusterDouble::colMax)
        .def("height", &ClusterDouble::height)
        .def("width", &ClusterDouble::width)
        .def("intensity", &ClusterDouble::intensity)
        .def("peakPixelIntensity", &ClusterDouble::peakPixelIntensity)
        .def("eod", &ClusterDouble::eod)
        .def("__str__", &ClusterDouble::str)
        .def("print", &ClusterDouble::print);

    typedef ImageProcessingDouble::Centroid CentroidDouble;
    bp::class_<CentroidDouble>
        ("Centroid", bp::init<>())
        .def(bp::init<ClusterDouble>())
        .def(bp::init<CentroidDouble>())
        .def("row", &CentroidDouble::row)
        .def("col", &CentroidDouble::col)
        .def("intensity", &CentroidDouble::intensity)
        .def("eod", &CentroidDouble::eod)
        .def("__str__", &CentroidDouble::str)
        .def("print", &CentroidDouble::print)
        .def("__eq__", &CentroidDouble::operator==)
        .def("__ne__", &CentroidDouble::operator!=)
        .def("__lt__", &CentroidDouble::operator<);

    bp::class_<std::vector<ClusterDouble> >("cluster_vector")
        .def(bp::vector_indexing_suite<std::vector<ClusterDouble> >());

    bp::class_<std::vector<CentroidDouble> >("centroid_vector")
        .def(bp::vector_indexing_suite<std::vector<CentroidDouble> >());

    bp::class_<ImageProcessingDouble>
        ("ImageProcessing", bp::init<>())
        .def("applyThreshold", &ImageProcessingDouble::applyThreshold).staticmethod("applyThreshold")
        .def("centroidClusters", &ImageProcessingDouble::centroidClusters).staticmethod("centroidClusters")
        .def("clusterPixels", &ImageProcessingDouble::clusterPixels).staticmethod("clusterPixels")
        .def("generateThreshold", &ImageProcessingDouble::generateThreshold).staticmethod("generateThreshold")
        .def("generateCentroids", &ImageProcessingDouble::generateCentroids).staticmethod("generateCentroids")
        .def("windowExceedances", &ImageProcessingDouble::windowExceedances).staticmethod("windowExceedances");

    // Coordinates
    typedef Coordinates::RA<double> RaDouble;
    typedef Coordinates::RA<float> RaFloat;
    typedef Coordinates::Dec<double> DecDouble;
    typedef Coordinates::Dec<float> DecFloat;
    typedef Coordinates::Coordinate<double> CoordinateDouble;
    typedef Coordinates::Coordinate<float> CoordinateFloat;

    bp::class_<RaDouble>
        ("RaDouble", bp::init<>())
        .def(bp::init<double>())
        .def(bp::init<uint8, uint8, double>())
        .def(bp::init<RaDouble>())
        .def("asFloat", &RaDouble::astype<float>)
        .def("degrees", &RaDouble::degrees)
        .def("radians", &RaDouble::radians)
        .def("hours", &RaDouble::hours)
        .def("minutes", &RaDouble::minutes)
        .def("seconds", &RaDouble::seconds)
        .def("__str__", &RaDouble::str)
        .def("print", &RaDouble::print)
        .def("__eq__", &RaDouble::operator==)
        .def("__ne__", &RaDouble::operator!=)
        .def("print", &RaInterface::print<double>);

    bp::class_<RaFloat>
        ("RaFloat", bp::init<>())
        .def(bp::init<double>())
        .def(bp::init<uint8, uint8, double>())
        .def(bp::init<RaFloat>())
        .def("asDouble", &RaFloat::astype<double>)
        .def("degrees", &RaFloat::degrees)
        .def("radians", &RaFloat::radians)
        .def("hours", &RaFloat::hours)
        .def("minutes", &RaFloat::minutes)
        .def("seconds", &RaFloat::seconds)
        .def("__str__", &RaFloat::str)
        .def("print", &RaFloat::print)
        .def("__eq__", &RaFloat::operator==)
        .def("__ne__", &RaFloat::operator!=)
        .def("print", &RaInterface::print<float>);

    bp::enum_<Coordinates::Sign::Type>("Sign")
        .value("POSITIVE", Coordinates::Sign::POSITIVE)
        .value("NEGATIVE", Coordinates::Sign::NEGATIVE);

    bp::class_<DecDouble>
        ("DecDouble", bp::init<>())
        .def(bp::init<double>())
        .def(bp::init<Coordinates::Sign::Type, uint8, uint8, double>())
        .def(bp::init<DecDouble>())
        .def("asFloat", &DecDouble::astype<float>)
        .def("sign", &DecDouble::sign)
        .def("degrees", &DecDouble::degrees)
        .def("radians", &DecDouble::radians)
        .def("degreesWhole", &DecDouble::degreesWhole)
        .def("minutes", &DecDouble::minutes)
        .def("seconds", &DecDouble::seconds)
        .def("__str__", &DecDouble::str)
        .def("print", &DecDouble::print)
        .def("__eq__", &DecDouble::operator==)
        .def("__ne__", &DecDouble::operator!=)
        .def("print", &DecInterface::print<double>);

    bp::class_<DecFloat>
        ("DecFloat", bp::init<>())
        .def(bp::init<float>())
        .def(bp::init<Coordinates::Sign::Type, uint8, uint8, float>())
        .def(bp::init<DecFloat>())
        .def("asDouble", &DecFloat::astype<double>)
        .def("sign", &DecFloat::sign)
        .def("degrees", &DecFloat::degrees)
        .def("radians", &DecFloat::radians)
        .def("degreesWhole", &DecFloat::degreesWhole)
        .def("minutes", &DecFloat::minutes)
        .def("seconds", &DecFloat::seconds)
        .def("__str__", &DecFloat::str)
        .def("print", &DecFloat::print)
        .def("__eq__", &DecFloat::operator==)
        .def("__ne__", &DecFloat::operator!=)
        .def("print", &DecInterface::print<float>);

    bp::class_<CoordinateDouble>
        ("CoordinateDouble", bp::init<>())
        .def(bp::init<double, double>())
        .def(bp::init<uint8, uint8, double, Coordinates::Sign::Type, uint8, uint8, double>())
        .def(bp::init<double, double, double>())
        .def(bp::init<RaDouble, DecDouble>())
        .def(bp::init<NdArrayDouble>())
        .def(bp::init<CoordinateDouble>())
        .def("asFloat", &CoordinateDouble::astype<float>)
        .def("dec", &CoordinateDouble::dec, bp::return_internal_reference<>())
        .def("ra", &CoordinateDouble::ra, bp::return_internal_reference<>())
        .def("x", &CoordinateDouble::x)
        .def("y", &CoordinateDouble::y)
        .def("z", &CoordinateDouble::z)
        .def("xyz", &CoordinateDouble::xyz)
        .def("degreeSeperation", &CoordinateInterface::degreeSeperationCoordinate<double>)
        .def("degreeSeperation", &CoordinateInterface::degreeSeperationVector<double>)
        .def("radianSeperation", &CoordinateInterface::radianSeperationCoordinate<double>)
        .def("radianSeperation", &CoordinateInterface::radianSeperationVector<double>)
        .def("__str__", &CoordinateDouble::str)
        .def("print", &CoordinateDouble::print)
        .def("__eq__", &CoordinateDouble::operator==)
        .def("__ne__", &CoordinateDouble::operator!=)
        .def("print", &CoordinateInterface::print<double>);

    bp::class_<CoordinateFloat>
        ("CoordinateFloat", bp::init<>())
        .def(bp::init<float, float>())
        .def(bp::init<uint8, uint8, float, Coordinates::Sign::Type, uint8, uint8, float>())
        .def(bp::init<float, float, float>())
        .def(bp::init<RaFloat, DecFloat>())
        .def(bp::init<NdArrayFloat>())
        .def(bp::init<CoordinateFloat>())
        .def("asDouble", &CoordinateFloat::astype<double>)
        .def("dec", &CoordinateFloat::dec, bp::return_internal_reference<>())
        .def("ra", &CoordinateFloat::ra, bp::return_internal_reference<>())
        .def("x", &CoordinateFloat::x)
        .def("y", &CoordinateFloat::y)
        .def("z", &CoordinateFloat::z)
        .def("xyz", &CoordinateFloat::xyz)
        .def("degreeSeperation", &CoordinateInterface::degreeSeperationCoordinate<float>)
        .def("degreeSeperation", &CoordinateInterface::degreeSeperationVector<float>)
        .def("radianSeperation", &CoordinateInterface::radianSeperationCoordinate<float>)
        .def("radianSeperation", &CoordinateInterface::radianSeperationVector<float>)
        .def("__str__", &CoordinateFloat::str)
        .def("print", &CoordinateFloat::print)
        .def("__eq__", &CoordinateFloat::operator==)
        .def("__ne__", &CoordinateFloat::operator!=)
        .def("print", &CoordinateInterface::print<float>);

    // DataCube
    typedef DataCube<double> DataCubeDouble;
    bp::class_<DataCubeDouble>
        ("DataCube", bp::init<>())
        .def(bp::init<uint32>())
        .def("at", &DataCubeInterface::at<double>, bp::return_internal_reference<>())
        .def("__getitem__", &DataCubeInterface::getItem<double>, bp::return_internal_reference<>())
        .def("back", &DataCubeDouble::back, bp::return_internal_reference<>())
        .def("dump", &DataCubeDouble::dump)
        .def("front", &DataCubeDouble::front, bp::return_internal_reference<>())
        .def("isempty", &DataCubeDouble::isempty)
        .def("shape", &DataCubeDouble::shape, bp::return_internal_reference<>())
        .def("size", &DataCubeDouble::size)
        .def("pop_back", &DataCubeDouble::pop_back)
        .def("pop_front", &DataCubeDouble::pop_front)
        .def("push_back", &DataCubeDouble::push_back)
        .def("push_front", &DataCubeDouble::push_front);
}
