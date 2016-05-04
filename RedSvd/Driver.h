// RedSvd.h

#pragma once

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;

#include "redsvd.hpp"

namespace REDSVD {

	public ref class Driver
	{
	public:
		void ComputeSvdExact(IEnumerable<cli::array<double>^>^ input, int numberOfRows, int numberOfColumns, [Out] cli::array<double>^% singularValues, [Out] cli::array<double>^% U_VT_columnwise);
		void ComputeSvdRandomized(IEnumerable<cli::array<double>^>^ input, int numberOfRows, int numberOfColumns, int rank, [Out] cli::array<double>^% singularValues, [Out] cli::array<double>^% U_VT_columnwise);
	};
}
