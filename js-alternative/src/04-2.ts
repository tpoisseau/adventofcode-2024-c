import { readFileSync } from 'node:fs';

const input = readFileSync('../inputs/04.txt', { encoding: 'utf8' }).split(
  '\n',
);

const nRows = input.length;
const nCols = input[0].length;

let occurrences = 0;
for (let row = 1; row < nRows - 1; row++) {
  const line = input[row];

  for (let col = 1; col < nCols - 1; col++) {
    const char = line[col];
    if (char !== 'A') continue;

    if (!isCrossMAS(input, row, col)) continue;

    occurrences++;
  }
}

// return next letter to check or false
function isMOrS(char: string): 'M' | 'S' | false {
  if (char === 'M') return 'S';
  if (char === 'S') return 'M';

  return false;
}

function isCrossMAS(input: string[], row: number, col: number) {
  { // top right MAS - SAM
    const nextLetter = isMOrS(input[row+1][col+1]);
    if (!nextLetter) return false;
    if (input[row-1][col-1] !== nextLetter) return false;
  }

  { // top left MAS - SAM
    const nextLetter = isMOrS(input[row+1][col-1]);
    if (!nextLetter) return false;
    if (input[row-1][col+1] !== nextLetter) return false;
  }

  return true;
}

console.log(occurrences);
