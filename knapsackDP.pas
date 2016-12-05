program knapsackDP;
uses crt;
var
	n,k,i,j : integer;
	w,p : array of integer;
	m : array of array of longint;
begin
	clrscr;
	writeln('input :');
	readln(n);
	setlength(w, n); setlength(p, n);
	for i:=1 to n do readln(w[i], p[i]);
	readln(k);
	setlength(m, n+1, k+1);
	for i:=0 to k do m[0,i] := 0;
	for i:=1 to n do
		for j:=0 to k do
		begin
				if w[i] > j then m[i,j] := m[i-1,j]
				else
					if m[i-1,j] > m[i-1,j-w[i]] + p[i] then m[i,j] := m[i-1,j]
					else m[i,j] := m[i-1,j-w[i]] + p[i];
		end;
	writeln('output :');
	writeln(m[n][k]);	
	readln;
end.