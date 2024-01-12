#include "js_output.hpp"
#include "../../libs/webview/webview.h"
#include <iostream>

extern webview::webview * globalw;

std::string js;

void evalJs() {
	globalw->eval(js);
}

void globalJsEval(const std::string& inputjs) {
	std::cerr << "JS: <" << inputjs << ">" << std::endl;
	js = inputjs;

	globalw->dispatch(evalJs);
}