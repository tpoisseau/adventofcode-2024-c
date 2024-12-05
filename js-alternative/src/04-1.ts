import { readFileSync } from 'node:fs';

const input = readFileSync('../inputs/04.txt', { encoding: 'utf8' }).split(
  '\n',
);

const nRows = input.length;
const nCols = input[0].length;

const searchVectors = [
  [0, 1],
  [1, 1],
  [1, 0],
  [1, -1],
  [0, -1],
  [-1, -1],
  [-1, 0],
  [-1, 1],
];

const search = 'XMAS';
let occurrences = 0;
for (let row = 0; row < nRows; row++) {
  const line = input[row];

  for (let col = 0; col < nCols; col++) {
    const char = line[col];
    if (char !== 'X') continue;

    vector: for (const [mRow, mCol] of searchVectors) {
      for (let searchIndex = 1; searchIndex < search.length; searchIndex++) {
        const searchLetter = search[searchIndex];

        const cRow = row + mRow * searchIndex;
        if (cRow < 0 || cRow >= nRows) continue vector;

        const cCol = col + mCol * searchIndex;
        if (cCol < 0 || cCol >= nCols) continue vector;

        const char = input[cRow][cCol];

        if (searchLetter !== char) continue vector;
      }

      occurrences++;
    }
  }
}

console.log(occurrences);
