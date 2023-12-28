#include "js_output.hpp"
#include "../../libs/webview/webview.h"

extern webview::webview * globalw;

void globalJsEval(const std::string& js) {
	globalw->dispatch(
		[&js]() {
			globalw->eval(js);
		}
	);
}