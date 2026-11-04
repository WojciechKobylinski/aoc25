
def mul(lst):
    result = 1
    for x in lst:
        result *= x
    return result

def part1():
    with open('long6.txt') as f:
        first_line = True
        RESULT = 0
        cols = []
        for line in f:
            index = 0
            # print (f"index {index}")
            for x in line.split():
                # print (f"x {x}")
                if x == '*':
                    m = mul(cols[index])
                    # print (f"RAZY {m}=={cols[index]}")
                    RESULT += m
                elif x == '+':
                    a = sum(cols[index])
                    RESULT += a
                    # print (f"PLUS {a}=={cols[index]}")
                elif first_line:
                    cols.append([int(x)])
                else:
                    cols[index].append(int(x))
                index += 1
                # print (f"index {index}")
            first_line = False
        print (RESULT)


with open('long6.txt') as f:
    lines = []
    for line in f:
        lines.append(line)
    last = lines[-1]
    acc = 0
    result = 0
    for i in range(len(last)):
        if last[i] == '*':
            # print (f"ADD MUL {acc}")
            result += acc
            state='*'
            acc = 1
        elif last[i] == '+':
            # print (f"ADD ADD {acc}")
            result += acc
            state = '+'
            acc = 0
        digits = []
        for line in lines[0:len(lines)-1]:  # wszystkie oprócz ostatniej
            if (line[i] != ' '):
                digits.append(line[i])
        print (digits)
        if digits == []:
            val = 0
        else:
            val = int("".join(str(d) for d in digits))
        # print (f"VAL {val}")
        if val > 0:
            acc = acc * val if state == '*' else acc + val
        # print (f"ACC {acc}")
    result += acc

    print (f"Result: {result}")



