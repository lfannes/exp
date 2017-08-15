task :run_old do
    cflags = `pkg-config --cflags sfml-all`.chomp
    libs = `pkg-config --libs sfml-all`.chomp
	sh "g++ main.cpp -o main #{cflags} #{libs}"
	sh'./main'
end

task :run do
    sh "cook -a x64 sfml#exe"
    sh "./sfml.exe"
end
