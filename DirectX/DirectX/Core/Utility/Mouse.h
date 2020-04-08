﻿//--------------------------------------------------------------------------------------
// File: Mouse.h
//
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
//
// http://go.microsoft.com/fwlink/?LinkId=248929
// http://go.microsoft.com/fwlink/?LinkID=615561
//--------------------------------------------------------------------------------------

#pragma once

#include <windows.h>
#include <memory>

namespace DirectX
{
	class Mouse
	{
	public:
		Mouse() noexcept(false);
		Mouse(Mouse&& moveFrom) noexcept;
		Mouse& operator= (Mouse&& moveFrom) noexcept;

		Mouse(Mouse const&) = delete;
		Mouse& operator=(Mouse const&) = delete;

		virtual ~Mouse();

		enum Mode
		{
			MODE_ABSOLUTE = 0,// 绝对坐标模式，每次状态更新xy值为屏幕像素坐标，且鼠标可见
			MODE_RELATIVE, // 相对运动模式，每次状态更新xy值为每一帧之间的像素位移量，且鼠标不可见
		};

		struct State
		{
			bool    leftButton;         // 鼠标左键被按下
			bool    middleButton;       // 鼠标滚轮键被按下
			bool    rightButton;        // 鼠标右键被按下
			bool    xButton1;           // 忽略
			bool    xButton2;           // 忽略
			int     x;                  // 绝对坐标x或相对偏移量
			int     y;                  // 绝对坐标y或相对偏移量
			int     scrollWheelValue;   // 滚轮滚动累积值
			Mode    positionMode;       // 鼠标模式
		};

		class ButtonStateTracker
		{
		public:
			enum ButtonState
			{
				UP = 0,         // Button is up
				HELD = 1,       // Button is held down
				RELEASED = 2,   // Button was just released
				PRESSED = 3,    // Buton was just pressed
			};

			ButtonState leftButton;
			ButtonState middleButton;
			ButtonState rightButton;
			ButtonState xButton1;
			ButtonState xButton2;

#pragma prefast(suppress: 26495, "Reset() performs the initialization")
			ButtonStateTracker() noexcept { Reset(); }
			// 在每一帧的时候应提供Mouse的当前状态去更新它
			void __cdecl Update(const State& state);

			void __cdecl Reset() noexcept;
			// 获取上一帧的鼠标事件，应当在Update之前使用，否则变为获取当前帧的状态
			State __cdecl GetLastState() const { return lastState; }

		private:
			State lastState;
		};

		// Retrieve the current state of the mouse
		State __cdecl GetState() const;

		// Resets the accumulated scroll wheel value
		void __cdecl ResetScrollWheelValue();

		// Sets mouse mode (defaults to absolute)
		void __cdecl SetMode(Mode mode);

		// Feature detection
		bool __cdecl IsConnected() const;

		// Cursor visibility
		bool __cdecl IsVisible() const;
		void __cdecl SetVisible(bool visible);

#if !defined(WINAPI_FAMILY) || (WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP) && defined(WM_USER)
		void __cdecl SetWindow(HWND window);
		static void __cdecl ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam);
#endif
		// Singleton
		static Mouse& __cdecl Get();

	private:
		// Private implementation.
		class Impl;

		std::unique_ptr<Impl> pImpl;
	};
}