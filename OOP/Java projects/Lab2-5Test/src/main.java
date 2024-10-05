///////////////////////// Class GUI  ////////////////////////////////
import javax.swing.Box;
import javax.swing.ImageIcon;
import javax.swing.JComponent;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.border.EmptyBorder;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableModel;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import javax.swing.*;


public class GUI extends JFrame{

    //Объявляем массивы
    String elements[];
    Object headers[];
    Object data[][];
    String sorting[];

    // Объявляем контейнеры
    JMenuBar menuBar;
    JMenu fileMenu;
    JMenuItem saveMenuIt,openMenuIt,newMenuIt,extMenuIt;

    JTable table;
    DefaultTableModel tableModel;

    JLabel search_label,sortingLabel;
    JComboBox сomboBox,sortingCombolBox;
    JToolBar toolBar;
    JTextField search_field;
    JButton button_search;
    JButton button_save,button_open,button_add,button_edit,button_delete,button_profile;
    JTextArea textArea;
    Box box1,box2,box3;

    // Объявляем классы
    iHandler ihandler = new iHandler();
    Mouse Ms = new Mouse();
    LisT Ls = new LisT();

    public GUI(){
        super("Библиотека");

        //Размер экрана
        setSize(1100,600);
        setDefaultCloseOperation(EXIT_ON_CLOSE);

        // Инцилизация массивов
        elements = new String[] {"Ключевому слову","Автору","Книге","Году издания","В наличие"};
        sorting = new String[] {"Автору","Книге","Году издания","Наличию"};
        headers = new Object[] {"Автор","Книга","Год издания","Наличие"};
        data = new Object[50][4] ;

        //Инцилизация контейнеров
        search_label = new JLabel("Поиск по:");
        сomboBox = new JComboBox(elements);
        toolBar = new JToolBar("Инструментальная панель");
        search_field = new JTextField("Введите данные");
        button_search = new JButton("Поиск");
        tableModel = new DefaultTableModel(data, headers);
        table =new JTable(tableModel);
        sortingLabel = new JLabel("Сортировка по");
        sortingCombolBox = new JComboBox(sorting);
        textArea = new JTextArea(20,30);
        textArea.setLineWrap(true);// Перенос текста
        textArea.setWrapStyleWord(true);// Перенос слова целеком на соседнию строку
        //textArea.append("Область для ввода текстового содержимого ");
        menuBar = new JMenuBar();
        fileMenu = new JMenu("Файл");
        openMenuIt = new JMenuItem("Открыть");
        saveMenuIt = new JMenuItem("Сохранить");
        newMenuIt = new JMenuItem("Новое");
        extMenuIt = new JMenuItem("Выйти");

        // Создаём кнопки и задаём им значки
        button_save = new JButton(new ImageIcon("./16x16/29.png"));
        button_open = new JButton(new ImageIcon("./16x16/46.png"));
        button_add = new JButton(new ImageIcon("./16x16/20.png"));
        button_edit = new JButton(new ImageIcon("./16x16/36.png"));
        button_delete = new JButton(new ImageIcon("./16x16/17.png"));
        button_profile = new JButton(new ImageIcon("./16x16/11.png"));

        // Настройка подсказок для кнопок
        button_save.setToolTipText("Сохранить список книг");
        button_open.setToolTipText("Открыть список книг");
        button_add.setToolTipText("Добавить информацию");
        button_edit.setToolTipText("Редактировать");
        button_delete.setToolTipText("Удалить информацию о книге");
        button_profile.setToolTipText("Профиль администратора");

        // Изменяем размер кнопок
        button_save.setPreferredSize(new Dimension(25,25));
        button_open.setPreferredSize(new Dimension(25,25));
        button_add.setPreferredSize(new Dimension(25,25));
        button_edit.setPreferredSize(new Dimension(25,25));
        button_delete.setPreferredSize(new Dimension(25,25));
        button_profile.setPreferredSize(new Dimension(25,25));
        ;

        //Создаём меню
        Menu();

        //Создаём меня поиска сортировки
        Bar();

        // Все созданные и расположенные элементы выводим на окно
        getContentPane().add(toolBar, BorderLayout.NORTH);
        getContentPane().add(new JScrollPane(textArea), BorderLayout.EAST);
        getContentPane().add(new JScrollPane(table));


        сomboBox.addActionListener(ihandler);
        //search_field.addActionListener(ihandler);
        extMenuIt.addActionListener(ihandler);
        button_open.addActionListener(ihandler);
        button_save.addActionListener(ihandler);

        search_field.addMouseListener(Ms);


        ListSelectionModel selModel = table.getSelectionModel();
        selModel.addListSelectionListener(Ls);

    }

    private void Menu(){
        // Создаём меню
        fileMenu.add(newMenuIt);
        fileMenu.add(openMenuIt);
        fileMenu.add(saveMenuIt);
        fileMenu.addSeparator();
        fileMenu.add(extMenuIt);

        //Загружаем меню
        menuBar.add(fileMenu);
        menuBar.add(Box.createHorizontalGlue());
        setJMenuBar(menuBar);

    }

    private void Bar(){
        // Вставляем кнопки в панель инструментов
        box1 = Box.createHorizontalBox();
        box1.add(button_save);
        box1.add(Box.createHorizontalStrut(3));
        box1.add(button_open);
        box1.add(Box.createHorizontalStrut(3));
        box1.add(button_profile);
        box1.add(Box.createHorizontalStrut(3));
        box1.add(new JSeparator(SwingConstants.VERTICAL));
        box1.add(Box.createHorizontalStrut(3));
        box1.add(button_add);
        box1.add(Box.createHorizontalStrut(3));
        box1.add(button_delete);
        box1.add(Box.createHorizontalStrut(3));
        box1.add(button_edit);


        // Создаём поисковую строку
        box2 = Box.createHorizontalBox();
        box2.add(search_label);
        box2.add(Box.createHorizontalStrut(6));
        box2.add(сomboBox);
        box2.add(Box.createHorizontalStrut(6));
        box2.add(search_field);
        box2.add(Box.createHorizontalStrut(6));
        box2.add(button_search);
        box2.add(Box.createHorizontalStrut(6));
        box2.add(button_search);

        // Создаём строку для сортировки
        box3 = Box.createHorizontalBox();
        box3.add(sortingLabel);
        box3.add(Box.createHorizontalStrut(6));
        box3.add(sortingCombolBox);

        // Объединяем все три строки
        toolBar.add(box1, BorderLayout.WEST);
        toolBar.add(Box.createHorizontalStrut(12));
        toolBar.add(new JSeparator(SwingConstants.VERTICAL));
        toolBar.add(Box.createHorizontalStrut(12));
        toolBar.add(box2);
        toolBar.add(Box.createHorizontalStrut(12));
        toolBar.add(new JSeparator(SwingConstants.VERTICAL));
        toolBar.add(Box.createHorizontalStrut(12));
        toolBar.add(box3, BorderLayout.EAST);

        //Лишаем возможность перемещать панель
        toolBar.setFloatable(false);
    }

    public class iHandler implements ActionListener{

        public void actionPerformed(ActionEvent e) {
            if(e.getSource() == сomboBox){
                //search_field.setText("По " + (String) сomboBox.getSelectedItem());
                search_field.setText("Введите данные");
            }

            if(e.getSource() == search_field){
                search_field.setText("");
            }

            if(e.getSource() == extMenuIt){
                dispose();
            }

            if(e.getSource() == button_open){
                FileOpen file = new FileOpen("Открытие данных",tableModel);
            }

            if(e.getSource() == button_save){
                FileSave file = new FileSave("Сохранение данных",tableModel);

            }
        }
    }

    public class Mouse implements MouseListener{

        public void mouseClicked(MouseEvent e) {

            // Если строка в строке search_field, есть первичная запись из elements, то она удаляется
            if((search_field.getText().contains("Введите данные")))
			/*
			if((search_field.getText().contains(elements[0])) || (search_field.getText().contains(elements[1]))
					||(search_field.getText().contains(elements[2])) || (search_field.getText().contains(elements[3]))
					||(search_field.getText().contains(elements[4])))*/
                search_field.setText("");
        }


        public void mouseEntered(MouseEvent e) {}

        public void mouseExited(MouseEvent e) {}

        public void mousePressed(MouseEvent e) {}

        public void mouseReleased(MouseEvent e) {}

    }

    public class LisT implements ListSelectionListener{

        public void valueChanged(ListSelectionEvent e) {
            textArea.setText("");
            FileOpenText text = new FileOpenText(textArea,"2.txt");
        }
    }
}

///////////////////////// Password  ////////////////////////////////


import javax.swing.*;
        import javax.swing.border.EmptyBorder;

import java.awt.*;
        import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;


public class Password extends JFrame {

    Handler handler = new Handler();
    Box box1,box2,box3,mainBox;
    JButton button_ok,button_cancel,button_registration;
    JTextField FieldLogin;
    JLabel LableLogin,passwLabel;
    JPasswordField passwField;

    public Password(){
        super("Регистрация читателя");
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setResizable(false);

        // Настраиваем первую горизонтальную панель (для ввода идентификатора или ФИО)
        box1 = Box.createHorizontalBox();
        LableLogin = new JLabel("Введите логин");
        FieldLogin = new JTextField(20);
        box1.add(LableLogin);
        box1.add(Box.createHorizontalStrut(14));
        box1.add(FieldLogin);

        box2 = Box.createHorizontalBox();
        passwLabel = new JLabel ("Введите пароль");
        passwField = new JPasswordField (20);
        box2.add(Box.createHorizontalGlue());
        box2.add(passwLabel);
        box2.add(Box.createHorizontalStrut(6));
        box2.add(passwField);

        // Настраиваем вторую горизонтальную панель (с кнопками)
        box3 = Box.createHorizontalBox();
        button_ok = new JButton("Начать работу");
        button_cancel = new JButton("Отмена");
        button_registration = new JButton("Регестрация");
        box3.add(Box.createHorizontalGlue());
        box3.add(button_registration);
        box3.add(Box.createHorizontalStrut(12));
        box3.add(button_ok);
        box3.add(Box.createHorizontalStrut(12));
        box3.add(button_cancel);

        // Размещаем три горизонтальные панели на одной вертикальной
        mainBox = Box.createVerticalBox();
        mainBox.setBorder(new EmptyBorder(12,12,12,12));
        mainBox.add(box1);
        mainBox.add(Box.createVerticalStrut(12));
        mainBox.add(box2);
        mainBox.add(Box.createVerticalStrut(17));
        mainBox.add(box3);
        setContentPane(mainBox);
        pack();

        passwField.addActionListener(handler);
        button_ok.addActionListener(handler);
        button_cancel.addActionListener(handler);
        button_registration.addActionListener(handler);

    }

    public class Handler implements ActionListener{//implements - взаймсвенный метод
        public void actionPerformed(ActionEvent e) {
            // Метод действия(нажатия кнопки) преевод : действи выполнено
            if((e.getSource() == button_ok) || (e.getSource() == passwField)){
                try{

                    //Проверка ввода ФИО
                    String strLogin;
                    strLogin = FieldLogin.getText();
                    if(strLogin.length() == 0) throw new NullPointerException();

                    //Проверка ввода пароля
                    String strPassw;
                    strPassw = passwField.getText();
                    if(strPassw.length() == 0) throw new myException();


                    //Проверка на правильность пароля
                    String str;
                    str=passwField.getText();
                    if(!str.equals("2340612340")) throw new myException();

                    //JOptionPane.showMessageDialog(null,"Вход разрешен!");
                    //Запись в файл и запускаем другое окно
                    GUI r = new GUI();
                    r.setVisible(true);
                    r.setLocationRelativeTo(null);
                    dispose();

                } catch (NullPointerException ex) {
                    JOptionPane.showMessageDialog(null,"<html><p> Введите логин </p> ",
                            "Ошибка", JOptionPane.WARNING_MESSAGE);
                } catch (myException meEx) {
                    JOptionPane.showMessageDialog(null,meEx.getMessage());
                };

            }

            if(e.getSource() == button_cancel){
                dispose();
            }

            if(e.getSource() == button_registration){
                Registration list = new Registration("Регестрация");
                list.setVisible(true);
                list.setLocationRelativeTo(null);
            }
        }
    }

    private class myException extends Exception{
        public myException(){
            super("Пароль не верен!");
            passwField.setText("");

        }
    }
}

/////////////////////////////////// FileSave  ////////////////////////////////


import java.awt.FileDialog;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

import javax.swing.JFrame;
import javax.swing.table.DefaultTableModel;


public class FileSave extends JFrame {
    public FileSave(String str,DefaultTableModel table){
        FileDialog sava = new FileDialog(this,str,FileDialog.SAVE);
        sava.setFile("*.txt");// Установка начального каталога
        sava.setVisible(true);
        //Определяем имя каталога или файла
        String fileNameSave = sava.getDirectory() + sava.getFile();
        if(fileNameSave == null) return; // Пользователь нажал отмена
        try{
            BufferedWriter writer = new BufferedWriter(new FileWriter(fileNameSave));
            for(int i = 0; i < table.getRowCount(); i++){
                writer.write("\r\n");
                for(int j = 0; j < table.getColumnCount(); j++){
                    writer.write((String)table.getValueAt(i,j));
                    if(j<4) writer.write("|");
                }
            }
            writer.close();

        }catch (IOException e) {
            e.printStackTrace();
        }
    }
}


/////////////////////////////////// FileOpen  ////////////////////////////////


import java.awt.FileDialog;
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

import javax.swing.JFrame;
import javax.swing.JTable;
import javax.swing.table.DefaultTableModel;


public class FileOpen extends JFrame{

    public FileOpen(String str,DefaultTableModel table){
        FileDialog open = new FileDialog(this,str,FileDialog.LOAD);
        open.setFile("*.txt");// Установка начального каталога
        open.setVisible(true);
        //Определяем имя каталога или файла
        String fileNameOpen = open.getDirectory() + open.getFile();
        if(fileNameOpen == null) return; // Пользователь нажал отмена

        try{
            // Считываем строку и заносим в буфер
            BufferedReader reader = new BufferedReader(new FileReader(fileNameOpen));
            int rows = table.getRowCount();
            for(int i = 0; i < rows; i++)
                table.removeRow(0);
            String author;
            do{
                author = reader.readLine();
                if(author != null){
                    String[] str1 = author.split("\\|");
                    if(str1.length == 4)
                        table.addRow(new String[] {str1[0],str1[1],str1[2],str1[3]} );
                }
            }while(author != null);
            reader.close();
        }catch(FileNotFoundException e) {
            e.printStackTrace();
        }catch (IOException e) {
            e.printStackTrace();
        }
    }
}


//////////////////////////////////////// main  ///////////////////////////////////


import javax.swing.*;

public class main {

    public static void main(String arts[]){
        GUI r = new GUI();
        r.setVisible(true);
        r.setLocationRelativeTo(null);
    }
}
