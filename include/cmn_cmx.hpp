auto cmn = [](auto&& a, auto b){ if (a > b) {a = b; return true;} return false; };
auto cmx = [](auto&& a, auto b){ if (a < b) {a = b; return true;} return false; };
