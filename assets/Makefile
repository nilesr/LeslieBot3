SVGS=$(wildcard *.svg)
PNGS=$(patsubst %.svg,%.png,$(SVGS))

%.png: %.svg
	convert $^ $@

logos.h: $(PNGS) process.py logos.h.header logos.h.trailer
	cp logos.h.header logos.h
	for png in $(PNGS) ; do \
		echo Starting $$png ; \
		python3 process.py $$png >> logos.h ; \
	done
	cat logos.h.trailer >> logos.h
