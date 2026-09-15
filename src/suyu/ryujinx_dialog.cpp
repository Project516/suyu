// SPDX-FileCopyrightText: Copyright 2025 suyu Emulator Project
// SPDX-License-Identifier: GPL-3.0-or-later

#include <filesystem>
#include "qt_common/util/fs.h"
#include "ryujinx_dialog.h"
#include "ui_ryujinx_dialog.h"

namespace fs = std::filesystem;

RyujinxDialog::RyujinxDialog(std::filesystem::path suyu_path, std::filesystem::path ryu_path,
                             QWidget* parent)
    : QDialog(parent), ui(new Ui::RyujinxDialog), m_suyu(suyu_path.make_preferred()),
      m_ryu(ryu_path.make_preferred()) {
    ui->setupUi(this);

    connect(ui->suyu, &QPushButton::clicked, this, &RyujinxDialog::fromSuyu);
    connect(ui->ryujinx, &QPushButton::clicked, this, &RyujinxDialog::fromRyujinx);
}

RyujinxDialog::~RyujinxDialog() {
    delete ui;
}

void RyujinxDialog::fromSuyu() {
    accept();
    QtCommon::FS::LinkRyujinx(m_suyu, m_ryu);
}

void RyujinxDialog::fromRyujinx() {
    accept();
    QtCommon::FS::LinkRyujinx(m_ryu, m_suyu);
}
