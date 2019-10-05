import os
import ycm_core
from clang_helpers import PrepareClangFlags

# Set this to the absolute path to the folder (NOT the file!) containing the
# compile_commands.json file to use that instead of 'flags'. See here for
# more details: http://clang.llvm.org/docs/JSONCompilationDatabase.html
# Most projects will NOT need to set this to anything; you can just change the
# 'flags' list of compilation flags. Notice that YCM itself uses that approach.
compilation_database_folder = '/home/jahova/projects/avr/atmega328p/blinkLED'

# These are the compilation flags that will be used in case there's no
# compilation database set.
flags = [
'-D__AVR_ATxmega328p',
# THIS IS IMPORTANT! Without a "-std=<something>" flag, clang won't know which
# language to use when compiling headers. So it will guess. Badly. So C++
# headers will be compiled as C headers. You don't want that so ALWAYS specify
# a "-std=<something>".
# For a C project, you would set this to something like 'c99' instead of
# 'c++11'.
'-std=c99',
# ...and the same thing goes for the magic -x option which specifies the
# language that the files to be compiled are written in. This is mostly
# relevant for c++ headers.
# For a C project, you would set this to 'c' instead of 'c++'.
'-x c'
'-isystem',
'/usr/local/avr/avr/include',
'-isystem',
'/usr/local/avr/include',
'-DF_CPU=32000000UL',
'-DARCH=ARCH_XMEGA',
'-DF_USB=48000000',
'-DBOARD=BOARD_NONE',
'-DFLASH_SIZE_BYTES=128000',
'-DBOOTLOADER_SEC_SIZE_BYTES=8192',
'-DUSB_DEVICE_ONLY',
'-DNO_STREAM_CALLBACKS',
'-DINTERRUPT_CONTROL_ENDPOINT',
'-DUSE_FLASH_DESCRIPTORS',
'-DUSE_STATIC_OPTIONS="(USB_DEVICE_OPT_FULLSPEED | USB_OPT_PLLCLKSRC)"',
'-DFIXED_CONTROL_ENDPOINT_SIZE=32',
'-DFIXED_NUM_CONFIGURATIONS=1',
'-DMPU9150',
'-Os',
'-funsigned-char',
'-fpack-struct',
'-fshort-enums',
'-Wall',
'-Wstrict-prototypes',
'-I',
'.',
'-I',
'./DMP/',
'-I',
'./LUFA/Common/',
'-I',
'./LUFA/Drivers/Board/',
'-I',
'./LUFA/Drivers/USB/Class/',
'-I',
'./LUFA/Drivers/USB/Class/Common/',
'-I',
'./LUFA/Drivers/USB/Class/Device/',
'-I',
'./LUFA/Drivers/USB/Core/',
'-I',
'./LUFA/Drivers/USB/',
'-I',
'./LUFA/Platform/',
'-I',
'./LUFA/Platform/XMEGA/',
'-I',
'./LUFA/',
'-I',
'./XMEGA/',
# This path is for AVR gcc. 
]

if compilation_database_folder:
  database = ycm_core.CompilationDatabase( compilation_database_folder )
else:
  database = None


def DirectoryOfThisScript():
  return os.path.dirname( os.path.abspath( __file__ ) )


def MakeRelativePathsInFlagsAbsolute( flags, working_directory ):
  if not working_directory:
    return flags
  new_flags = []
  make_next_absolute = False
  path_flags = [ '-isystem', '-I', '-iquote', '--sysroot=' ]
  for flag in flags:
    new_flag = flag

    if make_next_absolute:
      make_next_absolute = False
      if not flag.startswith( '/' ):
        new_flag = os.path.join( working_directory, flag )

    for path_flag in path_flags:
      if flag == path_flag:
        make_next_absolute = True
        break

      if flag.startswith( path_flag ):
        path = flag[ len( path_flag ): ]
        new_flag = path_flag + os.path.join( working_directory, path )
        break

    if new_flag:
      new_flags.append( new_flag )
  return new_flags


def FlagsForFile( filename ):
  if database:
    # Bear in mind that compilation_info.compiler_flags_ does NOT return a
    # python list, but a "list-like" StringVec object
    compilation_info = database.GetCompilationInfoForFile( filename )
    final_flags = PrepareClangFlags(
        MakeRelativePathsInFlagsAbsolute(
            compilation_info.compiler_flags_,
            compilation_info.compiler_working_dir_ ),
        filename )

  else:
    relative_to = DirectoryOfThisScript()
    final_flags = MakeRelativePathsInFlagsAbsolute( flags, relative_to )

  return {
    'flags': final_flags,
    'do_cache': True
  }
