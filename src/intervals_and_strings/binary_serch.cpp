#include <bits/stdc++.h>
using namespace std;
// begin
${1:int} ${2:ok}(${3:0}), ${4:ng}(${5:inf}), md;
while (${4:ng} - ${2:ok} > 1) {
  md = (${2:ok} + ${4:ng}) >> 1;
  if (${6:ck(md)}) ok = md;
  else ng = md;
}
// end
