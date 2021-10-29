package com.taosdata.jdbc;

import org.junit.After;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

import java.sql.*;
import java.util.ArrayList;
import java.util.Random;

public class ParameterBindTest {

    private static final String host = "master";

    private Connection conn;
    private Random random = new Random(System.currentTimeMillis());

    @Test
    public void test() {
        // given
        String sql = "insert into ? using ? tags(?, ?) values(?, ?, ?)";
//        String[] tbnames = {"t1", "t2", "t3"};
        String[] tbnames = {"t1"};
        String stbname = "weather";
        int rows = 10;

        // when
        try (TSDBPreparedStatement pstmt = conn.prepareStatement(sql).unwrap(TSDBPreparedStatement.class)) {
            for (int i = 0; i < tbnames.length; i++) {
                pstmt.setTableName(tbnames[0]);
                pstmt.setTagInt(0, random.nextInt(100));
                pstmt.setTagInt(1, random.nextInt(100));

                ArrayList<Long> timestampList = new ArrayList<>();
                long current = System.currentTimeMillis();
                for (int j = 0; j < rows; j++) {
                    timestampList.add(current + j);
                }
                pstmt.setTimestamp(0, timestampList);

                ArrayList<Integer> f1List = new ArrayList<>();
                for (int j = 0; j < rows; j++) {
                    f1List.add(random.nextInt());
                }
                pstmt.setInt(1, f1List);

                ArrayList<Integer> f2List = new ArrayList<>();
                for (int j = 0; j < rows; j++) {
                    f2List.add(random.nextInt());
                }
                pstmt.setInt(2, f2List);

                pstmt.columnDataAddBatch();
                pstmt.columnDataExecuteBatch();
                pstmt.columnDataClearBatch();
            }
            pstmt.columnDataCloseBatch();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        // then
        try (Statement stmt = conn.createStatement()) {
            ResultSet rs = stmt.executeQuery("select count(*) from " + stbname);
            while (rs.next()) {
                int count = rs.getInt(1);
                Assert.assertEquals(tbnames.length * rows, count);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    @Before
    public void before() {
        String url = "jdbc:TAOS://" + host + ":6030/?user=root&password=taosdata";
        try {
            conn = DriverManager.getConnection(url);
            Statement stmt = conn.createStatement();
            stmt.execute("drop database if exists test_pd");
            stmt.execute("create database if not exists test_pd");
            stmt.execute("use test_pd");
            stmt.execute("create table weather(ts timestamp, f1 int, f2 int) tags(t1 int, t2 int)");
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    @After
    public void after() {
        try {
            Statement stmt = conn.createStatement();
            stmt.execute("drop database if exists test_pd");
            if (conn != null)
                conn.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }


}
