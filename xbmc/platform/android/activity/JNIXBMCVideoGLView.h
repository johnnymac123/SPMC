#pragma once
/*
 *      Copyright (C) 2016 Christian Browet
 *      http://xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include <androidjni/JNIBase.h>

#include <androidjni/Context.h>
#include <androidjni/Rect.h>
#include <androidjni/Surface.h>
#include <androidjni/SurfaceHolder.h>

#include "guilib/Geometry.h"
#include "threads/Event.h"

class CJNIXBMCVideoGLView : virtual public CJNIBase
{
public:
  CJNIXBMCVideoGLView();
  CJNIXBMCVideoGLView(const jni::jhobject &object);
  ~CJNIXBMCVideoGLView();

  static void RegisterNatives(JNIEnv* env);

  static CJNIXBMCVideoGLView* GetInstance() { return m_lastInstance; }
  static CJNIXBMCVideoGLView* createVideoGLView();

  void surfaceChanged(int width, int height);
  void surfaceCreated();
  void onDrawFrame();

  void add();
  void release();
  bool isCreated() const;
  bool waitForSurface(unsigned int millis);
  void requestRender(bool clear, uint8_t alpha);

protected:
  CEvent m_surfaceCreated;
  static CJNIXBMCVideoGLView *find_instance(const jni::jhobject &o);

  static void _surfaceChanged(JNIEnv* env, jobject thiz, jint width, jint height);
  static void _surfaceCreated(JNIEnv* env, jobject thiz);
  static void _onDrawFrame(JNIEnv* env, jobject thiz);

private:
  bool m_lastClear;
  uint8_t m_lastAlpha;

  static CJNIXBMCVideoGLView* m_lastInstance;
  static std::list<std::pair<jni::jhobject, CJNIXBMCVideoGLView*>> m_object_map;
};
