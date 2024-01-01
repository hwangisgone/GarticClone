#include "js_output.hpp"
#include "../../libs/webview/webview.h"

extern webview::webview * globalw;

std::string js;

void evalJs() {
	globalw->eval(js);
}

void globalJsEval(const std::string& inputjs) {
	js = inputjs;

	globalw->dispatch(evalJs);
}