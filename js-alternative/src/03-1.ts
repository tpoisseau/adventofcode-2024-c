import { readFileSync } from "node:fs";

const input = readFileSync("../inputs/03.txt", { encoding: "utf8" });

const result = input
  .matchAll(/mul\((\d{1,3}),(\d{1,3})\)/g)
  .reduce((acc, [match, left, right]) => acc + Number(left) * Number(right), 0);

console.log(result);
