import { config } from 'eslint-config-zakodium';
import ts from 'eslint-config-zakodium/ts';
import unicorn from 'eslint-config-zakodium/unicorn';

export default config(
  {
    ignores: ['build'],
  },
  ...ts,
  ...unicorn,
  {
    rules: {
      'no-console': 'off',
    },
  },
);
