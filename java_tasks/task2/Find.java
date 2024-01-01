package task2;

import java.io.*;
import java.nio.file.*;
import java.nio.file.attribute.*;
import static java.nio.file.FileVisitResult.*;

public class Find {

    public static class Finder
            extends SimpleFileVisitor<Path> {

        private final PathMatcher matcher;
        private int numMatches = 0;

        Finder(String pattern) {
            matcher = FileSystems.getDefault()
                    .getPathMatcher("glob:" + pattern);
        }

        void find(Path file) {
            Path name = file.getFileName();
            if (name != null && matcher.matches(name)) {
                numMatches++;
                System.out.println(file);
            }
        }

        void done() {
            System.out.println("Matched: "
                    + numMatches);
        }

        @Override
        public FileVisitResult visitFile(Path file,
                BasicFileAttributes attrs) {
            find(file);
            return CONTINUE;
        }

        @Override
        public FileVisitResult preVisitDirectory(Path dir,
                BasicFileAttributes attrs) {
            find(dir);
            return CONTINUE;
        }

        @Override
        public FileVisitResult visitFileFailed(Path file,
                IOException exc) {
            System.err.println(exc);
            return CONTINUE;
        }
    }

    static void usage() {
        System.err.println("java Find <substring>" +
                " <optional_starting_directory>");
        System.exit(-1);
    }

    public static void main(String[] args)
            throws IOException {

        if (args.length != 1 && args.length != 2)
            usage();

        Path startingDir;

        if (args.length == 1) {
            startingDir = Paths.get(".");
        } else {
            startingDir = Paths.get(args[1]);
        }

        String pattern = "*" + args[0].replace(".", "?") + "*";

        System.out.println("Glob pattern: <" + pattern + ">");

        Finder finder = new Finder(pattern);
        Files.walkFileTree(startingDir, finder);
        finder.done();
    }
}
