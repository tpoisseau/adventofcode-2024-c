import { open } from 'node:fs/promises';

const input = await open('./inputs/01.txt');

const left: number[] = [];
const right: number[] = [];
for await (const line of input.readLines({ encoding: 'utf8' })) {
  const [a, b] = line.split('   ');
  left.push(Number(a));
  right.push(Number(b));
}

left.sort((a, b) => a - b);
right.sort((a, b) => a - b);

const distances: number[] = new Array(left.length);
for (let i = 0; i < left.length; i++) {
  distances[i] = Math.abs(left[i] - right[i]);
}

const totalDistance = distances.reduce((acc, d) => acc + d, 0);

console.log(totalDistance);
