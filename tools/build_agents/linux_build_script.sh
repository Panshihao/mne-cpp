# startdir = mne-cpp/tools/build_agents/
cd ../..
qmake -r
make -j4

# user package
tar cfvz binaries_only_unix.tar.gz bin lib

# development package
tar cfvz binaries_all_unix.tar.gz *
