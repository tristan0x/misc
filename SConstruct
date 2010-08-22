
import os

def create_environment ():
    os.environ['LD_LIBRARY_PATH'] = '/home/ken/lib:/usr/local/lib64'
    cpp_path_misc_library = os.path.join (os.getcwd (), 'src', 'include')

    env = Environment (CC='g++',
                       CPPFLAGS='-std=c++0x -pthread -Wall -O2',
                       ENV= os.environ,
                       CPPPATH=[cpp_path_misc_library])

    if int(ARGUMENTS.get('debug', 0)):
        env.Append(CCFLAGS = '-g')


    return env

env = create_environment ()
Export ('env')

SConscript (['src/impl/misc/SConscript', 'test/SConscript'], exports='env')
