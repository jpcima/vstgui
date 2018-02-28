// This file is part of VSTGUI. It is subject to the license terms 
// in the LICENSE file found in the top-level directory of this
// distribution and at http://github.com/steinbergmedia/vstgui/LICENSE

#ifndef __hiviewframe__
#define __hiviewframe__

#include "../../../cframe.h"

#if MAC_CARBON

#include "../../iplatformframe.h"
#include <Carbon/Carbon.h>

namespace VSTGUI {

extern bool isWindowComposited (WindowRef window);

//-----------------------------------------------------------------------------
class HIViewFrame : public IPlatformFrame
{
public:
	static void setAddToContentView (bool addToContentView); // defaults to true

	HIViewFrame (IPlatformFrameCallback* frame, const CRect& size, WindowRef parent);
	~HIViewFrame () noexcept;

	HIViewRef getPlatformControl () const { return controlRef; }
	const CPoint& getScrollOffset () const { return hiScrollOffset; }

	// IPlatformFrame
	bool getGlobalPosition (CPoint& pos) const override;
	bool setSize (const CRect& newSize) override;
	bool getSize (CRect& size) const override;
	bool getCurrentMousePosition (CPoint& mousePosition) const override;
	bool getCurrentMouseButtons (CButtonState& buttons) const override;
	bool setMouseCursor (CCursorType type) override;
	bool invalidRect (const CRect& rect) override;
	bool scrollRect (const CRect& src, const CPoint& distance) override;
	bool showTooltip (const CRect& rect, const char* utf8Text) override;
	bool hideTooltip () override;
	SharedPointer<IPlatformTextEdit> createPlatformTextEdit (IPlatformTextEditCallback* textEdit) override;
	SharedPointer<IPlatformOptionMenu> createPlatformOptionMenu () override;
#if VSTGUI_OPENGL_SUPPORT
	SharedPointer<IPlatformOpenGLView> createPlatformOpenGLView () override { return nullptr; } // not supported
#endif
	SharedPointer<IPlatformViewLayer> createPlatformViewLayer (IPlatformViewLayerDelegate* drawDelegate, IPlatformViewLayer* parentLayer = nullptr) override { return 0; } // not supported
	SharedPointer<COffscreenContext> createOffscreenContext (CCoord width, CCoord height, double scaleFactor = 1.) override;
	DragResult doDrag (IDataPackage* source, const CPoint& offset, CBitmap* dragBitmap) override;
	void setClipboard (const SharedPointer<IDataPackage>& data) override;
	SharedPointer<IDataPackage> getClipboard () override;
	PlatformType getPlatformType () const override { return PlatformType::kWindowRef; }

//-----------------------------------------------------------------------------
protected:
	static pascal OSStatus carbonMouseEventHandler (EventHandlerCallRef inHandlerCallRef, EventRef inEvent, void *inUserData);
	static pascal OSStatus carbonEventHandler (EventHandlerCallRef inHandlerCallRef, EventRef inEvent, void *inUserData);
	
	WindowRef window;
	HIViewRef controlRef;
	bool hasFocus;
	bool isInMouseTracking;
	EventHandlerRef mouseEventHandler;
	EventHandlerRef keyboardEventHandler;
	CPoint hiScrollOffset;
};

} // namespace

#endif // MAC_CARBON
#endif // __hiviewframe__
