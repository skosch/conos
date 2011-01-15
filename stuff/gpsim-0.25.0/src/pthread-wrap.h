
/*
   Copyright (C) 2004 T. Scott Dattalo

This file is part of the libgpsim library of gpsim

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, see 
<http://www.gnu.org/licenses/lgpl-2.1.html>.
*/

#if !defined(__PTHREAD_WRAP_H__)
#define __PTHREAD_WRAP_H__

#include <pthread.h>

namespace gpsim {

  /// ThreadWrapper
  /// a private implementation of pthread variables for the
  /// Token class. This is not intended to be used directly
  /// by modules.

  struct ThreadWrapper
  {
    /// pthread variables.
    pthread_t thHostInterface;
    pthread_attr_t thAttribute;
    pthread_mutex_t mutex;
    pthread_cond_t cvWaitOnParent;
    pthread_cond_t cvWaitOnChild;
  };
} // end of namespace gpsim

#endif // !defined(__PTHREAD_WRAP_H__)
