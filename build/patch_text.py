from textencoder import writeText
from getVersion import getVersion
rom_version = getVersion();

def PALifyText(input_text_arr):
    output = []
    for x in input_text_arr:
        temp = []
        for y in range(4):
            temp.append(x)
        output.append(temp)
    return output

dolby = [
    ["PRESENTED BY"], # Originally "PRESENTED IN"
    ["RED IS STINKY"], # Originally "DOLBY AND THE DOUBLE-D SYMBOL ARE"
    ["\0"], # Originally "TRADEMARKS OF DOLBY LABORATORIES."
]

main_menu = [
    # Barrel Screen
    ["PRACTICE"], # Originally "ADVENTURE"
    ["TUNES"], # Originally "SOUND"
    ["PUBG"], # Originally "KONG BATTLE"
    ["CHEATING"], # Originally "MYSTERY"
    ["MEMES"], # Originally "OPTIONS"
    # File Screen / File Deletion
    ["ERASE GAME"],
    ["EMPTY"],
    ["GAME"],
    ["ERASE"],
    ["ARE YOU SURE?"],
    ["NO"],
    ["YES"],
    # Multiplayer Menu
    ["MONKEY SMASH"],
    ["BATTLE ARENA"],
    ["ARENA"],
    # Multiplayer
    ["GAME TYPE"],
    ["SURVIVAL"],
    ["COIN HOARD"],
    ["WINS"],
    ["TIME"],
    ["CAPTURE"],
    ["CAPTURE PAD"],
    ["LIFE"],
    ["LIVES"],
    ["MIN"],
    ["MINS"],
    ["PAD"],
    ["PADS"],
    ["SCREEN TYPE"],
    ["LOSE"],
    ["WIN"],
    ["SCORE"],
    # Sound Menu
    ["SOUND"],
    ["MAIN"],
    ["SFX"],
    ["MUSIC"],
    ["RESET"],
    ["STEREO"],
    ["MONO"],
    ["SURROUND"],
    ["VOLUME"],
    # Options Menu
    ["OPTIONS"],
    ["SCREEN SIZE"],
    ["STORY SKIP"],
    ["RESET HISCORE"],
    ["CHIMPY CAM"],
    ["LANGUAGE"],
    ["NORMAL"],
    ["WIDESCREEN"],
    ["OFF"],
    ["ON"],
    ["ENGLISH"],
    ["FREE"],
    ["FOLLOW"],
    # Mystery Menu Sections
    ["MYSTERY"],
    ["DK THEATRE"],
    ["DK BONUS"],
    ["BOSSES"],
    ["BATTLE"],
    ["CHEATS"],
    # DK Theatre
    ["RAP"],
    ["INTRO STORY"],
    ["JUNGLE INTRO"],
    ["AZTEC INTRO"],
    ["FACTORY INTRO"],
    ["GALLEON INTRO"],
    ["FOREST INTRO"],
    ["CAVES INTRO"],
    ["CASTLE INTRO"],
    ["ENTER HIDEOUT"],
    ["K.ROOL PRESS BUTTON"],
    ["K.ROOL TAKEOFF"],
    ["GAME OVER"],
    ["END SEQUENCE"],
    # Bosses
    ["JUNGLE BOSS"],
    ["AZTEC BOSS"],
    ["FACTORY BOSS"],
    ["GALLEON BOSS"],
    ["FOREST BOSS"],
    ["CAVES BOSS"],
    ["CASTLE BOSS"],
    ["THE MAIN EVENT"],
    # DK Bonus
    ["RAMBI ARENA"],
    ["ENGUARDE ARENA"],
    ["DK ARCADE"],
    ["JETPAC"],
    # Cheats
    ["COINS"],
    ["AMMO"],
    ["ORANGES"],
    ["FILM"],
    ["CRYSTAL COCONUTS"],
    ["INSTRUMENTS"],
    ["ALL"],
    ["DEBUG POS"],
    # Krusha Enabled for Multiplayer
    ["KRUSHA"],
    # Highscores
    ["RAMBI HISCORE"],
    ["ENGUARDE HISCORE"],
    ["RAMBI ARENA"],
    ["ENGUARDE ARENA"],
    ["WELL DONE! ENTER YOUR NAME"],
    ["BAD LUCK: YOUR SCORE"],
    ["END MARKER"],
]

klumsy = [
    [
        "THE GANONDOOR GLITCH IN OCARINA OF TIME WAS CREATED DUE TO SHEER LAZINESS.",
        "BECAUSE WHAT THEY DID WAS THEY USED THE SAME EXACT DOOR FOR GOHMA THAT THEY USED FOR GANON'S CASTLE.",
        "SO WHEN YOU EDIT THE H- WHEN YOU USE THE GLITCH, WHAT IT DOES IS IT MAKES THE GAME THINK THAT YOU'RE ENTERING THE GANONDORF FIGHT",
        "AND WHEN YOU GO THROUGH GOHMA'S DOOR, IT TELEPORTS YOU TO THE GANONDORF FIGHT. IT WAS EITHER ZFG OR NARCISSA THAT FOUND IT."
    ], # K. Lumsy first Textbox
    [
        "I KNOW IT DOESN'T LOSE TIME TO GET A 53 IN NLE BUT IT'S NOT ABOUT THE TIME OF THE RUN,",
        "IT'S ABOUT THE MESSAGE YOU SEND TO THE WORLD THAT GETTING A 53 IN VINE BARREL IS AN OK THING TO DO."   
    ], # K. Lumsy second Textbox
    [
        "UM JAG, THANK YOU FOR THE RESPONSE IT IS MUCH APPRECIATED BUT YOU DON'T HAVE TO TYPE NO.",
        "NOT RESPONDING DOES THE SAME THING SO JUST TO LET YOU KNOW FOR NEXT TIME SO YOU DON'T WASTE YOUR TIME LIKE YOU'RE WASTING MINE."
    ], # Kong Textbox
    [
        "HEY 2DOS WHY DON'T YOU PLAY DK64 ANYMORE?",
        "I THINK IT'S PRETTY FKIN RUDE HOW YOU'RE ACTING RIGHT NOW.",
        "MOST PEOPLE ONLY FOLLOW FOR YOUR DK64 AND YOU'RE LOSING FOLLOWERS TONIGHT ACTING LIKE A CHILD."
    ], # K. Lumsy post-japes textbox
]

wrinkly = [
    [
        "WELCOME TO THE DONKEY KONG 64 PRACTICE ROM.",
        "I'M WRINKLY,YOUR LOW OPACITY COMPANION. I'M HERE TO PROVIDE YOU WITH SO MANY HINTS AND TIPS, YOU'D NEED TO WATCH AT LEAST 121 BISMUTH 'SPEEDRUN EXPLAINED' VIDEOS TO BE THIS INFORMED.",
        "ACROSS MY 35 DOORS YOU WILL DISCOVER MORE TIPS TO IMPROVING YOUR DK64 EXECUTION"], # FTT
    # Japes
    [
        "TO MOVE FASTER AS DK, ROLL AND RELEASE THE STICK WHEN YOUR SPEED HITS 250.",
        "WHEN YOUR SPEED DECREASES TO 150, MOVE THE STICK IN THE DIRECTION YOU WISH TO MOVE."
        "THIS SAVES ROUGHLY 1 FRAME PER ROLL.",
    ],
    [
        "DIDDY MOVES FASTEST WHEN YOU CARTWHEEL, THEN JUMP THEN AERIAL."
        "YOU WANT TO JUMP OUT OF THE CARTWHEEL AS SOON AS POSSIBLE AS THIS GIVES YOU 150 SPEED."
    ],
    [
        "LANKY MOVES FASTEST WHEN YOU START AN ORANGSTAND THEN JUMP AS SOON AS POSSIBLE.",
        "ONCE YOU LAND, COME OUT OF ORANGSTAND AND THEN START THE PROCESS AGAIN",
        "THIS IS SIGNIFICANTLY FASTER THAN A LONG JUMP, HITTING A PEAK OF 170 SPEED COMPARED TO THE LONG JUMP'S 150 SPEED."
    ],
    [
        "LONG JUMP IS FASTEST FOR TINY, BUT KICKSLIDE IS A GOOD WAY TO NAVIGATE CORNERS.",
        "HOWEVER, ONCE THE DUST STARTS FOR KICKSLIDES, IT IS BEST TO JUMP OUT TO INITIATE ANOTHER KICKSLIDE OR LONG JUMP SOONER."
    ],
    [
        "LONG JUMP IS CHUNKYS BEST MOVEMENT FOR RTA."
    ],
    # Aztec
    [
        "DK CAN GAIN A LOT OF HEIGHT WITH A MOONKICK FROM A FLOOR.",
        "IF YOU FIND YOURSELF SLAPPING INSTEAD OF KICKING, YOU WILL NEED TO MOVE FASTER."
    ],
    [
        "WITH THE USE OF 'CRASH CLIMB', DIDDY CAN GAIN THE MOST HEIGHT OF ALL.",
        "HOWEVER, THIS REQUIRES MULTIPLE FRAME-PERFECT INPUTS. FOR RTA, A MOONTAIL WILL SUFFICE IF YOU NEED EXTRA HEIGHT."
    ],
    [
        "LANKY CAN SCALE TALL STRUCTURES WITH A SKID-JUMP BACKFLIP.",
    ],
    [
        "TINY CAN SKID-JUMP, BUT IT'S SO WEAK THAT A BACKFLIP WILL BE ENOUGH FOR MOST SITUATIONS.",
    ],
    [
        "WHEN SKID-JUMP BACKFLIPPING, WAIT TO BACKFLIP A LITTLE LONGER AS CHUNKY. HIS SKID JUMP IS VERY FLOATY.",
    ],
    # Factory
    [
        "IF YOU ARE IN A BOSS FIGHT ON N64, ZOOM IN YOUR CAMERA AND TRY TO LOOK AWAY FROM OBJECTS.",
        "THIS CAN HELP SAVE MULTIPLE SECONDS IN A BOSS FIGHT INCLUDING K. ROOL.",
    ],
    [
        "THE SIDE WHICH THE GHOST SPAWNS ON IN KUT OUT IS THE SAME SIDE TO PHASE SWIM AT THE END OF THE FIGHT.",
        "HOWEVER, REMEMBER THAT IF YOU PHASE SWIM AS DIDDY IN THE FIGHT, THE FIGHT WILL INSTANTLY END."
    ],
    [
        "TO GET CLOSER TO THE STAR AT THE START OF EACH PHASE OF THE PUFFTOSS FIGHT, JUMP JUST BEFORE THE PUFFTOSS DAMAGE CUTSCENE STARTS.",
        "THE CUTSCENE WON'T HALT YOUR MOMENTUM WHEN JUMPING, SO WILL THEREFORE BE PRESERVED DURING THE CUTSCENE."
    ],
    [
        "THE AMOUNT OF TIMES MAD JACK JUMPS MAY SEEM RANDOM, HOWEVER THEY ARE NOT.",
        "IN ORDER OF THE PHASES, HE JUMPS 9, THEN 11, THEN 12, THEN 13, THEN 15 TIMES."
    ],
    [
        "LEARN TOES.TXT TO MAKE TINY PHASE EASIER.",
        "ASK THE DISCORD FOR THE PASTEBIN OR WRITE DOWN THE FOLLOWING SEQUENCE:",
        "PHASE 1 - 21221",
        "PHASE 2 - 21221 23322",
        "PHASE 3 - 23434 23344 43434",
        "PHASE 4 - 23434 23344 43434 23344",
    ],
    # Galleon
    [
        "PHASE SWIM, PHASEFALL AND PHASEWALK REQUIRE THE KONG TO BE FACING A CERTAIN WAY.",
        "MOST OF THE TIME, THEY REQUIRE YOU TO FACE BETWEEN 90 AND 180 DEGREES.",
        "HOWEVER, SOME PHASEWALKS DO ALLOW FOR AN ANGLE LESS THAN 90 DEGREES.",
        "USE THE ANGLE WATCH TO ASSIST WITH CONVERTING THOSE ANGLES TO THE DK64 WORLD.",
    ],
    [
        "THROWING ORANGES FASTER DOES NOT MEAN MORE LAG.",
        "SOMETIMES SPACING OUT YOUR ORANGE THROWS WILL MEAN THAT YOU WILL HAVE MORE CONSISTENT LAG CLIPS."
    ],
    [
        "EACH MOONKICK REQUIRES SLIGHTLY DIFFERENT TIMING, ESPECIALLY FOR LEDGE KICKS.",
        "THE PREMISE IS THAT YOU WANT TO KICK ON ONE OF THE FRAMES WHERE THE KONG IS TOUCHING THE GROUND",
        "FOR LEDGE KICKS, THIS ONLY WORKS FOR 1 FRAME. ADDITIONALLY, THE AERIAL ATTACK HAS TO BE WITHIN 8 FRAMES OF THE KICK.",
        "REMEMBER TO PRACTICE EACH MOONKICK IN THE CONTEXT YOU WILL BE DOING IT IN RUNS.",
    ],
    [
        "ALTHOUGH DIDDY DOESN'T GAIN HEIGHT DURING A SKID JUMP, IT STILL HAS USE.",
        "FOR EXAMPLE, YOU CAN STILL CROUCH OUT OF DIDDY'S SKID JUMP."
    ],
    [
        "HOLD A AFTER CANCELLING DKTV TO INSTANTLY SKIP THE BARREL PICKUP CUTSCENE UPON ENTERING THE MAIN MENU.",
        "NOT ONLY DOES THIS SAVE A COUPLE FRAMES, BUT THIS IS ALSO CRITICAL FOR SOME RUNS WHICH INVOLVE MMM.",
        "SINCE THE CUTSCENE IS INSTANTLY SKIPPED, YOU WILL NOT BE PULLED INTO INTRO STORY FROM THE BARREL PICKUP CUTSCENE.",
    ],
    # Fungi
    [
        "THE EXPANSION PAK WAS NOT A LAST MINUTE FIX.",
        "THE DEVELOPERS HAVE CONFIRMED THAT THEY WERE ASKED TO BUILD THE GAME AROUND THE USE OF THE EXPANSION PAK AT THE START OF DEVELOPMENT.",
    ],
    [
        "THERE ARE ONLY 16 RAINBOW COINS IN THE GAME, ALL HAVE BEEN FOUND.",
        "AS A RESULT, YOU CAN GET A TOTAL OF 400 COINS JUST FROM COLLECTING ALL THE RAINBOW COINS IN THE GAME",
    ],
    [
        "UNLIKE MOST COLLECTABLES IN THE GAME, THE BEAN INSIDE FUNGI FOREST IS NOT PERMANENTLY SAVED TO YOUR FILE",
        "AS A RESULT, IF YOU EXIT YOUR FILE AFTER COLLECTING THE BEAN, YOU WILL LOSE THE BEAN AND HAVE TO RECOLLECT IT.",
    ],
    [
        "REMEMBER TO ALWAYS FACE THE WINDOW OR THE COIN DOOR WHEN COLLECTING KEY 8.",
        "KEY 8 IS ONLY SAVED TO YOUR FILE IF YOU HAVE THE THRONE ROOM PART OF HIDEOUT HELM LOADED.",
        "NOT FACING THE WINDOW OR COIN DOOR MAY RESULT IN THE THRONE ROOM DELOADING AND THEREFORE WON'T SAVE KEY 8 TO YOUR FILE."
    ],
    [
        "IT IS POSSIBLE TO GET SOMETHING CALLED 'FAKE PRODUCTION ROOM'.",
        "THIS CAN BE PREVENTED BY GOING TO THE RIGHT HAND SIDE OF THE BEAVER BOTHER SPAWN SWITCH.",
        "THE 'FAKE PRODUCTION ROOM' WATCH SHOULD ASSIST WITH YOU LEARNING HOW TO PREVENT THIS."
    ],
    # Caves
    [
        "PRESS B AND THEN A TO CANCEL ANY LEVEL SIMIAN SLAM.",
        "IF THE SWITCH ISN'T PRESSED WHEN YOU DO THIS, YOU PRESSED B 1 FRAME TOO EARLY."
    ],
    [
        "PUTTING A KONG INBETWEEN A TORCH AND A WALL CAN OFTEN RESULT IN A WALL CLIP."
    ],
    [
        "LAG DOESN'T SPEED UP VERTICAL VELOCITY, SO IF YOU ARE FALLING IN ANY CAPACITY, IT IS BEST TO REDUCE LAG.",
    ],
    [
        "THERE ARE SEVERAL METHODS OF SKIPPING THE DANCE FROM A GOLDEN BANANA. THESE INCLUDE:",
        "- TAKING DAMAGE INTO IT.",
        "- GRABBING IT WHEN YOU ARE SUFFICIENTLY HIGH OFF THE GROUND.",
        "- PAUSE EXITING ON THE SAME FRAME YOU COLLECT IT.",
        "- COLLIDING WITH AN ORANGE WHILST DURING YOUR INVINCIBILITY FRAMES.",
        "- RESETTING THE GAME OR TOUCHING A LOADING ZONE DURING THE DANCE.",
    ],
    [
        "HOLD Z TO HOVER WHILST IN DIDDY'S ROCKETBARREL.",
        "THIS IS ESPECIALLY USEFUL IN DIDDY PHASE FOR DESTROYING THE TARGETS."
    ],
    # Castle
    [
        "YOU HAVE BEEN PLAYING THE DONKEY KONG 64 PRACTICE ROM."
    ],
    [
        "DEVELOPMENT TEAM: BALLAAM (HEAD DEVELOPER), RAIN (MEMORY VIEWER) AND ISOTARGE (ASSET INTEGRATION TOOL).",
    ],
    [
        "ADDITIONAL THANKS TO ALL THOSE IN THE DK64 SPEEDRUNNING DISCORD AND DK64 ROMHACKING DISCORD."
    ],
    [
        "EARLY VERSIONS (0.1 AND 0.2) CONSOLE TESTING DONE BY ZNERNICUS.",
    ],
    [
        "WEBSITE: DK64",
        "PRACTICEROM.COM",
    ],
]

if rom_version == 1:
    dolby = PALifyText(dolby);
    main_menu = PALifyText(main_menu);
    klumsy = PALifyText(klumsy);
    wrinkly = PALifyText(wrinkly);

writeText("dolby_text.bin",dolby);
writeText("menu_text.bin",main_menu);
writeText("klumsy_text.bin",klumsy);
writeText("wrinkly_text.bin",wrinkly);