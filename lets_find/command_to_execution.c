#include "minishell.h"

t_cmd *parse_every_command(t_token *token) {
    t_cmd *cmd_head = NULL;
    t_cmd *cmd_current = NULL;
    t_filedescriptiom *last_infile = NULL;
    t_filedescriptiom *last_outfile = NULL;

    while (token) {
        t_cmd *new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
        if (!new_cmd)
            return NULL;
        new_cmd->cmd = NULL;
        new_cmd->infile = NULL;
        new_cmd->outfile = NULL;
        new_cmd->next = NULL;

        t_token *temp = token;
        int nbr_of_args = 0;

        while (temp && strcmp(temp->type, "pipe") != 0) {
            if (strcmp(temp->type, "command") == 0 || strcmp(temp->type, "argument") == 0) {
                nbr_of_args++;
            }
            temp = temp->next;
        }

        new_cmd->cmd = (char **)malloc((nbr_of_args + 1) * sizeof(char *));
        if (!new_cmd->cmd)
            return NULL;

        int i = 0;
        while (token && strcmp(token->type, "pipe") != 0) {
            if (strcmp(token->type, "command") == 0 || strcmp(token->type, "argument") == 0) {
                new_cmd->cmd[i++] = strdup(token->token);
            } else if (strcmp(token->type, "in") == 0) {
                t_filedescriptiom *new_infile = (t_filedescriptiom *)malloc(sizeof(t_filedescriptiom));
                if (!new_infile)
                    return NULL;
                new_infile->filename = strdup(token->token);
                new_infile->isherdoc = 0;
                new_infile->iswithappend = 0;
                new_infile->next = NULL;

                if (token->prev && strcmp(token->prev->token, "<<") == 0) {
                    new_infile->isherdoc = 1;
                    new_infile->delimeter = token->token;
                }

                if (last_infile) {
                    last_infile->next = new_infile;
                } else {
                    new_cmd->infile = new_infile;
                }
                last_infile = new_infile;
            } else if (strcmp(token->type, "out") == 0) {
                t_filedescriptiom *new_outfile = (t_filedescriptiom *)malloc(sizeof(t_filedescriptiom));
                if (!new_outfile)
                    return NULL;
                new_outfile->filename = strdup(token->token);
                new_outfile->isherdoc = 0;
                new_outfile->iswithappend = 0;
                new_outfile->next = NULL;

                if (token->prev && strcmp(token->prev->token, ">>") == 0) {
                    new_outfile->iswithappend = 1;
                }

                if (last_outfile) {
                    last_outfile->next = new_outfile;
                } else {
                    new_cmd->outfile = new_outfile;
                }
                last_outfile = new_outfile;
            }
            token = token->next;
            //printf("the commnd %s", cmd_current->cmd[0]);
        }

        new_cmd->cmd[i] = NULL;

        if (cmd_current) {
            cmd_current->next = new_cmd;
        } else {
            cmd_head = new_cmd;
        }
        cmd_current = new_cmd;

        if (token) {
            token = token->next;
        }

        last_infile = NULL;
        last_outfile = NULL;
    }

    return cmd_head;
}
