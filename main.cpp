#include <wx\wx.h>
#include "TimerFrame.h"
class MyApp : public wxApp
{
public:
	virtual bool OnInit();
};
IMPLEMENT_APP(MyApp)
DECLARE_APP(MyApp)
bool MyApp::OnInit()
{
	TimerFrame *frame = new TimerFrame("Hungry Hungry Boy");
	frame->Show();
	return true;
}