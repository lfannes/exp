task :run do
sh 'g++ src/main.cpp -o main'
sh './main'
end