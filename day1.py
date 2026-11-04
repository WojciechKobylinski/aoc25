#!/usr/bin/env python3

def read_intervals_and_queries(filename: str):
    intervals, queries = [], []
    reading_intervals = True

    with open(filename) as f:
        for line in f:
            line = line.strip()
            if not line:
                reading_intervals = False
                continue
            if reading_intervals:
                L, R = map(int, line.split("-", 1))
                intervals.append((L, R))
            else:
                queries.append(int(line))
    return intervals, queries


def main1():
    intervals, queries = read_intervals_and_queries("short5.txt")

    sum = 0
    for q in queries:
        for (L, R) in intervals:
            if (q >= L) and (q <= R):
                sum += 1
                break

    print(f"\nSum: {sum}")
    return

def doStuff(intervals):
    merged = []

    for L, R in intervals:
        new_intervals = []
        curL, curR = L, R

        for a, b in merged:
            if b < curL - 1:
                new_intervals.append((a, b))
            elif curR < a - 1:
                new_intervals.append((curL, curR))
                curL, curR = a, b
            else:
                curL = min(curL, a)
                curR = max(curR, b)
        new_intervals.append((curL, curR))
        merged = new_intervals
    return merged


def main():
    intervals, queries = read_intervals_and_queries("long5.txt")
    merged = doStuff(intervals)
    result = 0
    for (L, R) in merged:
        result += R - L + 1
    print(f"\nSum: {result}")

if __name__ == "__main__":
    main()