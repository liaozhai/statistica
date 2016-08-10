/*
 * main.c
 *
 *  Created on: 9 рту. 2016 у.
 *      Author: marunov
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <glib.h>

gdouble** read_sample (const gchar* file, gint* pRows, gint* pCols);
gdouble** read_sample (const gchar* file, gint* pRows, gint* pCols){
	GError* err = NULL;
	gsize len;
	GIOChannel* gio = g_io_channel_new_file (file, "r", &err);
	if (gio == NULL) {
		g_error ("Unable to open file %s", file);
	}

	gint rows = 0;
	gint cols = 0;
	gchar* str = NULL;
	GArray* els = g_array_new (FALSE, FALSE, sizeof (gdouble));
	GIOStatus ret = g_io_channel_read_line (gio, &str, &len, NULL, &err);
	while (ret == G_IO_STATUS_NORMAL) {
		++rows;
		gchar** tokens = g_strsplit (str, "\t", G_MAXINT);
		for (gint i = 0; tokens[i] != NULL; ++i){
			gdouble v = g_ascii_strtod (tokens[i], NULL);
			g_array_append_val (els, v);
			cols = i;
		}
		g_free (str);
		g_free (tokens);
		ret = g_io_channel_read_line (gio, &str, &len, NULL, &err);
	};
	gint k = 0;
	gdouble** buf = malloc (sizeof (gdouble*) * rows);
	for (gint i = 0; i < rows; ++i){
		buf[i] = malloc (sizeof (gdouble) * cols);
		for (gint j = 0; j < cols; ++j){
			buf[i][j] = g_array_index (els, gdouble, k++);
		}
	}

	g_io_channel_shutdown(gio, TRUE, &err);

	*pRows = rows;
	*pCols = cols;

	return buf;

}

int main (int argc, char** argv){
	gint rows = 0;
	gint cols = 0;
	gdouble** sample = read_sample ("series.txt", &rows, &cols);
	for (gint i = 0; i < rows; ++i){
		printf ("%.2f", sample[0][0]);
		for (gint j = 1; j < cols; ++j){
			printf ("\t%.2f", sample[i][j]);
		}
		printf ("\n");
	}
	g_free (sample);
	return EXIT_SUCCESS;
}
