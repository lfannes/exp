task :run do
sh 'g++ src/main.cpp -o main -pthread'
sh './main'
end