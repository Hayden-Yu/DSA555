g++ -std=c++0x lab6.cpp timer.cpp 2>/dev/null
for j in 3 10 50 100 200 300 400 500 1000
do echo -e "<tr>\n<th>$j</th>"
    #./a.out $i
    #echo
    for i in 100000 200000 300000 400000
    do
        echo "<td>$(./a.out $i $j)</td>"
    done
    echo "</tr>"
done