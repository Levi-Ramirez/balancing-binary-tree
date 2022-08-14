// ============================================================================
// File: NotFoundException.h
// ============================================================================
// Header file for the class NotFoundException
// ============================================================================

#ifndef NOTFOUNDEXCEPTION_HEADER
#define NOTFOUNDEXCEPTION_HEADER

class NotFoundException
{
    public:
        NotFoundException(std::string errorMsg);

        std::string		GetMsg() const;
        void			SetMsg(std::string errorMsg);

    private:
        std::string 	m_errorMsg;

};

#endif
