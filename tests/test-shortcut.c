/**
 * vimb - a webkit based vim like browser.
 *
 * Copyright (C) 2012-2014 Daniel Carl
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see http://www.gnu.org/licenses/.
 */

#include <gtk/gtk.h>
#include <src/shortcut.h>

static void test_shortcut_single(void)
{
    char *uri;

    /* call with shortcut identifier */
    uri = shortcut_get_uri("_vimb1_ zero one");
    g_assert_cmpstr(uri, ==, "only-zero:zero%20one");
    g_free(uri);
}

static void test_shortcut_default(void)
{
    char *uri;

    /* call without shortcut identifier and if the last placeholder become the
     * none matched query words */
    uri = shortcut_get_uri("zero one two three");
    g_assert_cmpstr(uri, ==, "default:zero-two%20three");
    g_free(uri);
}

static void test_shortcut_keep_unmatched(void)
{
    char *uri;

    /* don't remove non matched placeholders */
    uri = shortcut_get_uri("zero");
    g_assert_cmpstr(uri, ==, "default:zero-$2");
    g_free(uri);
}

static void test_shortcut_fullrange(void)
{
    char *uri;

    /* check if all placeholders $0-$9 are replaced */
    uri = shortcut_get_uri("_vimb3_ zero one two three four five six seven eight nine");
    g_assert_cmpstr(uri, ==, "fullrange:zero-one-nine");
    g_free(uri);
}

static void test_shortcut_remove(void)
{
    char *uri;

    g_assert_true(shortcut_remove("_vimb4_"));

    /* check if the shortcut is really no used */
    uri = shortcut_get_uri("_vimb4_ test");
    g_assert_cmpstr(uri, ==, "default:_vimb4_-$2");
}

int main(int argc, char *argv[])
{
    int result;
    shortcut_init();

    g_assert_true(shortcut_add("_vimb1_", "only-zero:$0"));
    g_assert_true(shortcut_add("_vimb2_", "default:$0-$2"));
    g_assert_true(shortcut_add("_vimb3_", "fullrange:$0-$1-$9"));
    g_assert_true(shortcut_add("_vimb4_", "for-remove:$0"));
    g_assert_true(shortcut_set_default("_vimb2_"));

    g_test_init(&argc, &argv, NULL);

    g_test_add_func("/test-shortcut/get_uri/single", test_shortcut_single);
    g_test_add_func("/test-shortcut/get_uri/default", test_shortcut_default);
    g_test_add_func("/test-shortcut/get_uri/keep-unmatched", test_shortcut_keep_unmatched);
    g_test_add_func("/test-shortcut/get_uri/fullrange", test_shortcut_fullrange);
    g_test_add_func("/test-shortcut/remove", test_shortcut_remove);

    result = g_test_run();

    shortcut_cleanup();

    return result;
}
