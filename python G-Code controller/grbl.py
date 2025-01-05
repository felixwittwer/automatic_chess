from grbl_streamer import GrblStreamer

def my_callback(eventstring, *data):
    args = []
    for d in data:
        args.append(str(d))
    print("event={} data={}".format(eventstring.ljust(30), ", ".join(args)))

grbl = GrblStreamer(my_callback)
grbl.setup_logging()

grbl.cnect("COM8", 115200)

grbl.poll_start()

grbl.hash_state_requested = True

grbl.gcode_parser_state_requested = True

grbl.request_settings()

grbl.set_feed_override(True)
grbl.request_feed(10000)
grbl._stream("$H \n G92 X360 Y390 Z0 \n G1 X350 F10000 \n G92 X350 Y390 Z0 \n G1 X0 Y0 F10000 \n")
# grbl.stream("$H \n G92 X360 Y390 Z0 \n G1 X350 F10000 \n G92 X350 Y390 Z0 \n G1 X0 Y0 F10000 \n")

grbl.disconnect()