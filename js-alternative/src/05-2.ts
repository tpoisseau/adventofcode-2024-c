import { readFileSync } from 'node:fs';

import { DatabaseSync } from 'node:sqlite';

const db = new DatabaseSync(':memory:');
db.exec(`
CREATE TABLE IF NOT EXISTS rules (
    "left" INTEGER NOT NULL,
    "right" INTEGER NOT NULL
) STRICT;
CREATE INDEX IF NOT EXISTS rules_left_right_idx ON rules ("left", "right");
`);

const [rawRules, rawOrdering] = readFileSync('../inputs/05.txt', {
  encoding: 'utf8',
}).split('\n\n');

{
  const insertStatement = db.prepare(
    'INSERT INTO rules ("left", "right") VALUES (?, ?)',
  );
  for (const rawRule of rawRules.split('\n')) {
    const [left, right] = rawRule.split('|').map(Number);
    insertStatement.run(left, right);
  }
}

const ordering = rawOrdering
  .split('\n')
  .values()
  .filter(Boolean)
  .map((line) => line.split(',').map(Number));

const existsStatement = db.prepare(
  `SELECT "left", "right" FROM rules WHERE "left" = ? AND "right" = ?`,
);
let result = 0;
for (const order of ordering) {
  console.log('Order:', order);
  let needToSort = false;
  for (let h = 0, i = 1; i < order.length; h++, i++) {
    const page = order[i];
    const previousPage = order[h];

    const rule = existsStatement.get(page, previousPage);
    if (rule) {
      needToSort = true;
      break;
    }
  }

  if (!needToSort) continue;
  order.sort((a, b) => {
    if (existsStatement.get(a, b)) return -1;
    if (existsStatement.get(b, a)) return 1;
    return 0;
  });
  console.log('Ordered:', order);

  const middlePage = order[Math.floor(order.length / 2)];
  console.log('Middle page:', middlePage);

  result += middlePage;
}

console.log('Result:', result);
