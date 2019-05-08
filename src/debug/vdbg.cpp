// begin
{ // debug
  cout << "${1:おなまえ}: ";
  for (auto ${2:it} = $1.begin(); $2 != $1.end(); $2++) {
    ${3:cout << *it;}
    cout << (next($2) == $1.end() ? "\n" : ", ");
  }
  cout << endl;
} //
// end
