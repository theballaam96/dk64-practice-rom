import subprocess
import os
import shutil

WrinklyText = "Wrinkly_Copy.bin"

if os.path.exists(WrinklyText):
  os.remove(WrinklyText)

shutil.copyfile("Wrinkly.bin", WrinklyText);

with open(WrinklyText, "r+b") as fh:
  fh.seek(0x23F)
  fh.write("WELCOME TO THE DONKEY KONG 64 PRACTICE ROM. I'M WRINKLY,YOUR LOW OPACITY COMPANION HERE TO PROVIDE YOU WITH SO MANY HINTS AND TIPS, YOU'D NEED TO WATCH AT LEAST 121BISMUTH 'SPEEDRUNS EXPLAINED' VIDEOS TO BE THIS INFORMED. ACROSS MY 35 DOORS YOU WILL DISCOVER MORE TIPS TO IMPROVING YOUR DK64 EXECUTION\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0".encode("ascii"))
  # Japes
  fh.seek(0x3B9)
  fh.write("TO MOVE FASTER AS DK, ROLL N RELEASE THE STICK WHEN AT 250SPD, HOLD UP AT 150SPD.".encode("ascii"))
  fh.seek(0x40C)
  fh.write("DIDDY MOVES FASTEST WHEN YOU CARTWHEEL, THEN JUMP THEN AERIAL, HITTING A PEAK OF 150SPD.".encode("ascii"))
  fh.seek(0x464)
  fh.write("LANKY MOVES FASTEST WHEN YOU START AN ORANGSTAND THEN JUMP ASAP. THIS MAKES LANKY HIT 170 SPD!!".encode("ascii"))
  fh.seek(0x4C3)
  fh.write("LONG JUMP IS FASTEST FOR TINY, BUT KICKSLIDE IS A GOOD WAY TO NAVIGATE CORNERS.".encode("ascii"))
  fh.seek(0x512)
  fh.write("LONG JUMP IS CHUNKYS BEST MOVEMENT. IF YOU AREN'T A TAS, DON'T TWIRL.".encode("ascii"))
  # Aztec
  fh.seek(0x557)
  fh.write("DK CAN GAIN A LOT OF HEIGHT WITH A MOONKICK FROM A FLOOR.\0".encode("ascii"))
  fh.seek(0x591)
  fh.write("WITH THE USE OF CRASH CLIMB, DIDDY CAN GAIN THE MOST HEIGHT OF ALL.\0\0".encode("ascii"))
  fh.seek(0x5D6)
  fh.write("LANKY CAN SCALE TALL STRUCTURES WITH A SKID-JUMP BACKFLIP.\0\0\0\0".encode("ascii"))
  fh.seek(0x614)
  fh.write("TINY CAN SKID-JUMP, BUT IT'S SO WEAK THAT IT'S BEST TO BACKFLIP.\0\0\0".encode("ascii"))
  fh.seek(0x657)
  fh.write("WAIT TO BACKFLIP A LITTLE LONGER AS CHUNKY. HIS SKID JUMP IS VERY FLOATY.\0\0\0\0".encode("ascii"))
  # Factory
  fh.seek(0x6A4)
  fh.write("IF YOU ARE IN A BOSS FIGHT ON N64, ZOOM IN YOUR CAMERA! IT REDUCES LAG A TONNE.".encode("ascii"))
  fh.seek(0x6F3)
  fh.write("THE SIDE WHICH THE GHOST SPAWNS ON IN KUT OUT IS THE SAME SIDE TO PHASE SWIM.".encode("ascii"))
  fh.seek(0x740)
  fh.write("JUMPING BEFORE THE PUFFTOSS HIT CS STARTS MAKES MONKEY MOVE...\0\0\0".encode("ascii"))
  fh.seek(0x781)
  fh.write("MAD JACK JUMPS 9, 11, 12, 13 THEN 15 TIMES.\0\0\0\0\0".encode("ascii"))
  fh.seek(0x7B1)
  fh.write("LEARN TOES.TXT TO BE ABLE TO CAKEWALK THROUGH TINY PHASE!\0\0\0\0\0".encode("ascii"))
  # Galleon
  fh.seek(0x7EF)
  fh.write("PHASE SWIM, FALL AND WALK REQUIRE THE KONG TO BE FACING A CERTAIN WAY.\0".encode("ascii"))
  fh.seek(0x836)
  fh.write("THROWING ORANGES FASTER DOES NOT MEAN MORE LAG. TIMING IS KING HERE.".encode("ascii"))
  fh.seek(0x87A)
  fh.write("EACH MOONKICK REQUIRES SLIGHTLY DIFFERENT TIMING.\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0".encode("ascii"))
  fh.seek(0x8BB)
  fh.write("ALTHOUGH DIDDY DOESN'T GAIN HEIGHT DURING A SKID JUMP, IT STILL HAS USE.\0\0\0\0".encode("ascii"))
  fh.seek(0x907)
  fh.write("HOLD A TO INSTANTLY SKIP THE BARREL PICKUP CS IN THE MAIN MENU.\0".encode("ascii"))
  # Fungi
  fh.seek(0x947)
  fh.write("THE EXPANSION PAK WAS NOT A LAST MINUTE FIX.".encode("ascii"))
  fh.seek(0x973)
  fh.write("THERE ARE ONLY 16 RAINBOW COINS IN THE GAME, ALL HAVE BEEN FOUND".encode("ascii"))
  fh.seek(0x9B3)
  fh.write("IF YOU EXIT FILE AFTER COLLECTING THE BEAN, YOU WILL LOSE THE BEAN AND HAVE TO RECOLLECT IT.\0\0".encode("ascii"))
  fh.seek(0xA11)
  fh.write("MAD MAZE MAUL IS THE BEST MINIGAME IN DONKEY KONG 64.\0\0\0\0\0".encode("ascii"))
  fh.seek(0xA4B)
  fh.write("MORNIN'!\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0".encode("ascii"))
  # Caves
  fh.seek(0xA84)
  fh.write("PRESS B AND THEN A TO CANCEL ANY LEVEL SIMIAN SLAM.".encode("ascii"))
  fh.seek(0xAB7)
  fh.write("PUTTING A KONG INBETWEEN A TORCH AND A WALL IS A COMMON CLIP.\0\0\0".encode("ascii"))
  fh.seek(0xAF7)
  fh.write("LAG DOESN'T SPEED UP VERTICAL VELOCITY, SO REDUCE LAG TO FALL FASTER.\0\0\0\0".encode("ascii"))
  fh.seek(0xB40)
  fh.write("TAKING DAMAGE INTO A GOLDEN BANANA WILL SKIP THE DANCE.\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0".encode("ascii"))
  fh.seek(0xB8C)
  fh.write("HOLD Z TO HOVER WHILST IN DIDDY'S ROCKETBARREL.\0\0\0\0\0".encode("ascii"))
  # Castle
  fh.seek(0xBC0)
  fh.write("YOU HAVE BEEN PLAYING THE DONKEY KONG 64 PRACTICE ROM.\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0".encode("ascii"))
  fh.seek(0xC1D)
  fh.write("DK64 PRACTICE ROM MADE BY BALLAAM, RAIN AND ISOTARGE.\0\0\0\0".encode("ascii"))
  fh.seek(0xC56)
  fh.write("DK64 ROM HACKING THANKS TO ISOTARGE.\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0".encode("ascii"))
  fh.seek(0xC9A)
  fh.write("EARLY VERSIONS CONSOLE TESTING DONE BY ZNERNICUS.\0\0\0\0\0\0\0\0\0\0\0\0\0".encode("ascii"))
  fh.seek(0xCD8)
  fh.write("DK64 PRACTICEROM.COM\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0".encode("ascii"))