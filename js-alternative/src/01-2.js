import { open } from 'node:fs/promises';
const input = await open('./inputs/01.txt');
const left = [];
const right = new Map();
for await (const line of input.readLines({ encoding: 'utf-8' })) {
    const [_a, _b] = line.split('   ');
    const a = Number(_a);
    const b = Number(_b);
    left.push(a);
    right.has(b) ? right.set(b, right.get(b) + 1) : right.set(b, 1);
}
const distances = new Array(left.length);
for (let i = 0; i < left.length; i++) {
    const leftValue = left[i];
    const rightValue = right.get(left[i]) ?? 0;
    const similarity = leftValue * rightValue;
    distances[i] = similarity;
}
const totalDistance = distances.reduce((acc, d) => acc + d, 0);
console.log(totalDistance);
