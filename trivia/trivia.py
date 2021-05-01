#!/usr/bin/env python3
f = [x for x in open("/home/niles/trivia", "r").read().split("\n") if x != ""]
l = []
l.append("#pragma once")
l.append("")
l.append("// This file was autogenerated by trivia.py")
l.append("")
l.append("#define N_TRIVIA " + str(len(f)))
l.append("")
l.append("const char* trivia[N_TRIVIA] = {")
for w in f:
	l.append("    \"" + w.replace('"', '\\"') + "\",")
l.append("};")

open("trivia.h", "w").write("\n".join(l))
