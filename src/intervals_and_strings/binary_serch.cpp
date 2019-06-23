${1:int} ok = ${2:0}, ng = ${3:inf}, md;
while (abs(ok - ng) > 1) {
  md = (ok + ng) >> 1;
  if (${4:ck(md)}) ok = md;
  else ng = md;
}
