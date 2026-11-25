#include <stdlib.h>
#include <string.h>


typedef struct {
    int n;
    unsigned int mask;
    int queenColumns[9];

    char ***solutions;
    int *columnSizes;

    int count;
    int capacity;
} Context;

static void addSolution(Context *ctx) {
    if (ctx->count == ctx->capacity) {
        int newCapacity = ctx->capacity == 0
            ? 8
            : ctx->capacity * 2;

        char ***newSolutions = realloc(
            ctx->solutions,
            (size_t)newCapacity * sizeof(*newSolutions)
        );

        if (!newSolutions) return;

        ctx->solutions = newSolutions;

        int *newSizes = realloc(
            ctx->columnSizes,
            (size_t)newCapacity * sizeof(*newSizes)
        );

        if (!newSizes) return;

        ctx->columnSizes = newSizes;
        ctx->capacity = newCapacity;
    }

    char **board = malloc((size_t)ctx->n * sizeof(*board));

    if (!board) return;

    for (int row = 0; row < ctx->n; row++) {
        board[row] = malloc((size_t)ctx->n + 1);

        if (!board[row]) {
            for (int r = 0; r < row; r++) {
                free(board[r]);
            }

            free(board);
            return;
        }

        memset(board[row], '.', (size_t)ctx->n);

        board[row][ctx->queenColumns[row]] = 'Q';
        board[row][ctx->n] = '\0';
    }

    ctx->solutions[ctx->count] = board;
    ctx->columnSizes[ctx->count] = ctx->n;

    ctx->count++;
}

static void backtrack(
    Context *ctx,
    int row,
    unsigned int columns,
    unsigned int diagLeft,
    unsigned int diagRight
) {
    if (row == ctx->n) {
        addSolution(ctx);
        return;
    }

    unsigned int available = ctx->mask &
        ~(columns | diagLeft | diagRight);

    while (available) {
        unsigned int bit = available & (0u - available);
        available ^= bit;

        int col = 0;

        while (((bit >> col) & 1u) == 0u) {
            col++;
        }

        ctx->queenColumns[row] = col;

        backtrack(
            ctx,
            row + 1,
            columns | bit,
            ((diagLeft | bit) << 1) & ctx->mask,
            (diagRight | bit) >> 1
        );
    }
}

char*** solveNQueens(
    int n,
    int* returnSize,
    int** returnColumnSizes
) {
    Context ctx = {0};

    ctx.n = n;
    ctx.mask = (1u << n) - 1u;

    backtrack(&ctx, 0, 0u, 0u, 0u);

    *returnSize = ctx.count;
    *returnColumnSizes = ctx.columnSizes;

    return ctx.solutions;
}