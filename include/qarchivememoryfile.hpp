#ifndef QARCHIVE_MEMORY_FILE_HPP_INCLUDED
#define QARCHIVE_MEMORY_FILE_HPP_INCLUDED
#include <QBuffer>
#include <QJsonObject>

#include <memory>

#include "qarchive_global.hpp"

namespace QArchive {
class QARCHIVE_EXPORT MemoryFile {
public:
    MemoryFile(QJsonObject, std::shared_ptr<QBuffer>);
    MemoryFile() = default;
    ~MemoryFile() = default;

    [[gnu::warn_unused_result]] QJsonObject fileInformation() const;
    QBuffer* buffer() const;
    [[gnu::warn_unused_result]] std::shared_ptr<QBuffer> sharedBuffer() const;

private:
    QJsonObject m_FileInformation;
    std::shared_ptr<QBuffer> m_Buffer;
};
} // namespace QArchive

#endif // QARCHIVE_MEMORY_FILE_HPP_INCLUDED
