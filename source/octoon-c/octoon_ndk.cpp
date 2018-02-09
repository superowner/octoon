// +----------------------------------------------------------------------
// | Project : ray.
// | All rights reserved.
// +----------------------------------------------------------------------
// | Copyright (c) 2013-2015.
// +----------------------------------------------------------------------
// | * Redistribution and use of this software in source and binary forms,
// |   with or without modification, are permitted provided that the following
// |   conditions are met:
// |
// | * Redistributions of source code must retain the above
// |   copyright notice, this list of conditions and the
// |   following disclaimer.
// |
// | * Redistributions in binary form must reproduce the above
// |   copyright notice, this list of conditions and the
// |   following disclaimer in the documentation and/or other
// |   materials provided with the distribution.
// |
// | * Neither the name of the ray team, nor the names of its
// |   contributors may be used to endorse or promote products
// |   derived from this software without specific prior
// |   written permission of the ray team.
// |
// | THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// | "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// | LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// | A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// | OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// | SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// | LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// | DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// | THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// | (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// | OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// +----------------------------------------------------------------------
#if defined(_BUILD_PLATFORM_ANDROID)
#include <ray/ray.h>
#include <ray/ray_main.h>

#include <ray/game_application.h>

#include <ray/fcntl.h>
#include <ray/input.h>

#include <android_native_app_glue.h>

octoon::GameApplicationPtr g_gameApp;
octoon::util::string g_gameRootPath;
octoon::util::string g_gameScenePath;
bool _isQuitRequest = false;
android_app* _android_app = nullptr;

bool OctoonInit(const char* gamedir, const char* scenename) noexcept
{
	if (gamedir)
	{
		if (octoon::fcntl::access(gamedir, 0) == 0)
			g_gameRootPath = octoon::util::directory(gamedir);
	}

	if (scenename)
		g_gameScenePath = scenename;

	_isQuitRequest = false;

	return true;
}

void OctoonTerminate() noexcept
{
	OctoonCloseWindow();
}

bool OctoonOpenWindow(const char* title, int w, int h) noexcept
{
	g_gameApp = std::make_shared<octoon::GameApplication>();
	g_gameApp->setFileService(true);
	g_gameApp->setFileServicePath(g_gameRootPath);

	if (w == 0)
		w = _android_app->contentRect.right - _android_app->contentRect.left;
	if (h == 0)
		h = _android_app->contentRect.bottom - _android_app->contentRect.top;

	if (!g_gameApp->open(_android_app->window, w, h))
		return false;

	if (!g_gameScenePath.empty())
	{
		if (!g_gameApp->openScene(g_gameScenePath))
			return false;
	}

	return true;
}

void OctoonCloseWindow() noexcept
{
	if (g_gameApp)
	{
		g_gameApp.reset();
		g_gameApp = nullptr;
	}

	_isQuitRequest = true;
}

bool OctoonIsQuitRequest() noexcept
{
	return _isQuitRequest || _android_app->destroyRequested ? true : false;
}

void OctoonUpdate() noexcept
{
	if (g_gameApp)
		g_gameApp->update();
}

static int32_t onInputEvent(struct android_app* app, AInputEvent* event)
{
	int32_t lEventType = AInputEvent_getType(event);
	switch (lEventType)
	{
	case AINPUT_EVENT_TYPE_MOTION:
		switch (AInputEvent_getSource(event))
		{
		case AINPUT_SOURCE_TOUCHSCREEN:
			break;
		case AINPUT_SOURCE_TRACKBALL:
			break;
		}
	case AINPUT_EVENT_TYPE_KEY:
	{
		octoon::input::InputEvent inputEvent;
		inputEvent.event = octoon::input::InputEvent::Character;
		inputEvent.key.timestamp = ::AKeyEvent_getEventTime(event);
		inputEvent.key.state = true;

		inputEvent.key.keysym.raw = AKeyEvent_getScanCode(event);
		inputEvent.key.keysym.sym = AKeyEvent_getKeyCode(event);
		inputEvent.key.keysym.unicode = AKeyEvent_getKeyCode(event);
	}
	}

	int32_t id = AMotionEvent_getAction(event);
	switch (id)
	{
	case AMOTION_EVENT_ACTION_MOVE:
	{
		octoon::input::InputEvent inputEvent;
		inputEvent.event = octoon::input::InputEvent::TouchMotionMove;
		inputEvent.motion.x = ::AMotionEvent_getXOffset(event);
		inputEvent.motion.y = ::AMotionEvent_getYOffset(event);
		inputEvent.motion.xrel = inputEvent.motion.x;
		inputEvent.motion.yrel = inputEvent.motion.y;
		inputEvent.motion.state = ::AMotionEvent_getButtonState(event);
		inputEvent.motion.timestamp = ::AMotionEvent_getEventTime(event);
		inputEvent.button.button = octoon::input::InputButton::MOUSE0;
	}
	break;
	case AMOTION_EVENT_ACTION_DOWN:
	{
		octoon::input::InputEvent inputEvent;
		inputEvent.event = octoon::input::InputEvent::TouchMotionDown;
		inputEvent.motion.x = ::AMotionEvent_getXOffset(event);
		inputEvent.motion.y = ::AMotionEvent_getYOffset(event);
		inputEvent.motion.xrel = inputEvent.motion.x;
		inputEvent.motion.yrel = inputEvent.motion.y;
		inputEvent.motion.state = ::AMotionEvent_getButtonState(event);
		inputEvent.motion.timestamp = ::AMotionEvent_getDownTime(event);
		inputEvent.button.button = octoon::input::InputButton::MOUSE0;
	}
	break;
	case AMOTION_EVENT_ACTION_UP:
	{
		octoon::input::InputEvent inputEvent;
		inputEvent.event = octoon::input::InputEvent::TouchMotionUp;
		inputEvent.motion.x = ::AMotionEvent_getXOffset(event);
		inputEvent.motion.y = ::AMotionEvent_getYOffset(event);
		inputEvent.motion.xrel = inputEvent.motion.x;
		inputEvent.motion.yrel = inputEvent.motion.y;
		inputEvent.motion.state = ::AMotionEvent_getButtonState(event);
		inputEvent.motion.timestamp = ::AMotionEvent_getEventTime(event);
		inputEvent.button.button = octoon::input::InputButton::MOUSE0;
	}
	break;
	case AMOTION_EVENT_ACTION_CANCEL:
	{
		octoon::input::InputEvent inputEvent;
		inputEvent.event = octoon::input::InputEvent::TouchMotionCancel;
		inputEvent.motion.x = ::AMotionEvent_getXOffset(event);
		inputEvent.motion.y = ::AMotionEvent_getYOffset(event);
		inputEvent.motion.xrel = inputEvent.motion.x;
		inputEvent.motion.yrel = inputEvent.motion.y;
		inputEvent.motion.state = ::AMotionEvent_getButtonState(event);
		inputEvent.motion.timestamp = ::AMotionEvent_getEventTime(event);
		inputEvent.button.button = octoon::input::InputButton::MOUSE0;
	}
	break;
	}

	return 1;
}

void onAppCmd(struct android_app* app, int32_t cmd)
{
}

void android_main(android_app* app)
{
	_android_app = app;
	_android_app->onAppCmd = &onAppCmd;
	_android_app->onInputEvent = &onInputEvent;

	ray_main(0, 0);
}

#endif