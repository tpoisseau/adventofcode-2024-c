import { readFileSync } from "node:fs";

const input = readFileSync("../inputs/03.txt", { encoding: "utf8" });

const matches = input.matchAll(/mul\((\d{1,3}),(\d{1,3})\)|do\(\)|don\'t\(\)/g);

let mul = true;
let result = 0;
for (const [match, left, right] of matches) {
  if (match == "do()") {
    mul = true;
    continue;
  }

  if (match == "don't()") {
    mul = false;
    continue;
  }

  if (!mul) continue;
  result += Number(left) * Number(right);
}

console.log(result);
