sleep 1
for i in {1..1000}; do
    ./bin/sdstore proc-file -p 1 input.txt output.txt bcompress bcompress >> output1.txt &
done